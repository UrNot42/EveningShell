/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:05:52 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 13:16:13 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get from the compounds the amount of certain type of compound
 *
 * @param compound structure countaining those elements
 * @param is_cmd a bool to specify which type we are looking for
 * @return said amount
 */
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

/**
 * @brief frees every element of the exec struct
 * /!\ it doesn't close existing files
 *
 * @param exec the said structure
 * @param env bool value to specify if the environment oughts to be freed or not
 */
void	free_exec(t_exec *exec, bool env)
{
	free(exec->pi.ds);
	free(exec->cmd);
	free(exec->files);
	free_compound(exec->allocated_content);
	if (env)
		ft_free_dstr(*exec->env);
}

/**
 * @brief initialises the pipe structure
 * which deals with commands interaction and pids
 *
 * @param pi
 * @param size
 * @return int
 */
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

/**
 * @brief Set the execute struct object to values we can get from compound
 *
 * @param compound
 * @param ex
 * @param env
 * @return errors encountered or not
 */
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
	if (!ex->cmd)
		return (1);
	ex->cmd[ex->cmd_size] = (t_cmd){0};
	ex->file_size = get_compound_type_size(compound, false);
	ex->files = ft_calloc(ex->file_size + 1, sizeof(t_file));
	if (!ex->files)
		return (1);
	ex->files[ex->file_size] = (t_file){0};
	if (fill_file(compound, ex->files, ex->file_size))
		return (1);
	ex->pipe_size = fill_cmds(compound, ex->cmd, ex->files);
	return (0);
}
