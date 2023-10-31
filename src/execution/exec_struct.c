/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:05:52 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/31 16:43:54 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_token_type_size(t_token *token, bool is_cmd)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	if (is_cmd)
	{
		while (token[i].content)
			if (token[i++].type == CMD)
				++size;
		return (size);
	}
	while (token[i].content)
	{
		if (token[i].type == REDIR_IN || token[i].type == REDIR_OUT
			|| token[i].type == APPEND || token[i].type == HERE_DOC)
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
	free_token(ex->allocated_content);
	if (env)
		ft_free_dstr(ex->env);
}

int	set_execute_struct(t_token *token, t_exec *ex, char **env)
{
	ex->env = env;
	if (!token)
		return (1);
	ex->allocated_content = token;
	ex->cmd_size = get_token_type_size(token, true);
	ex->pi.ds = ft_calloc(ex->cmd_size + 1, sizeof(int));
	ex->pi.ds[ex->cmd_size] = -1;
	ex->pi.pe_prev = -1;
	ex->pi.pe[0] = -1;
	ex->pi.pe[1] = -1;
	ex->cmd = ft_calloc(ex->cmd_size + 1, sizeof(t_cmd));
	ex->cmd[ex->cmd_size] = (t_cmd){0};
	if (!ex->cmd)
		return (1);
	ex->file_size = get_token_type_size(token, false);
	ex->files = ft_calloc(ex->file_size + 1, sizeof(t_file));
	ex->files[ex->file_size] = (t_file){0};
	if (!ex->files)
		return (free(ex->cmd), 1);
	if (fill_file(token, ex->files, ex->file_size))
		return (1);
	if (fill_cmds(token, ex->cmd, ex->files))
		return (1);
	return (0);
}
