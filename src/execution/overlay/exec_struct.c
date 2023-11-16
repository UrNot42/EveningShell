/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:05:52 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 12:23:54 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_compound_type_size(t_compound *compound, bool is_cmd)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	if (is_cmd)
	{
		while (compound[i].content)
			if (compound[i++].type == PIPE)
				++size;
		return (size + 1);
	}
	while (compound[i].content)
	{
		if (compound[i].type == REDIR_IN || compound[i].type == REDIR_OUT
			|| compound[i].type == APPEND || compound[i].type == HERE_DOC)
			++size;
		i++;
	}
	return (size);
}

void	free_exec(t_exec *ex, bool env)
{
	free(ex->pi.ds);
	free(ex->cmd);
	free(ex->files);
	free_compound(ex->allocated_content);
	if (env)
		ft_free_dstr(*ex->env);
}

int	init_pipe(t_pipe *pi, int size)
{
	pi->ds = ft_calloc(size + 1, sizeof(int));
	if (!pi->ds)
		return (1);
	pi->ds[size] = -1;
	pi->pe_prev = -1;
	pi->pe[0] = -1;
	pi->pe[1] = -1;
	return (0);
}

int	set_execute_struct(t_compound *compound, t_exec *ex, char ***env)
{
	ex->env = env;
	if (compound[0].type == UNSET)
		return (1);
	ex->allocated_content = compound;
	ex->cmd_size = get_compound_type_size(compound, true);
	if (init_pipe(&ex->pi, ex->cmd_size))
		return (1);
	ex->cmd = ft_calloc(ex->cmd_size + 1, sizeof(t_cmd));
	ex->cmd[ex->cmd_size] = (t_cmd){0};
	if (!ex->cmd)
		return (1);
	ex->file_size = get_compound_type_size(compound, false);
	ex->files = ft_calloc(ex->file_size + 1, sizeof(t_file));
	ex->files[ex->file_size] = (t_file){0};
	if (!ex->files)
		return (1);
	if (fill_file(compound, ex->files, ex->file_size))
		return (1);
	ex->pipe_size = fill_cmds(compound, ex->cmd, ex->files);
	return (0);
}
