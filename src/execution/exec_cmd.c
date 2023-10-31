/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:47:21 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/31 11:02:13 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO
int	execute_builtin(t_exec *ex, int i)
{
	(void)ex;
	(void)i;
	return (1);
}

int	open_fd(t_cmd *cmd, t_pipe pi)
{
	if (cmd->in != NULL && cmd->in->exists)
	{
		if (cmd->in->fd == -1)
			return (perror(cmd->in->name), 1);
		dup2(cmd->in->fd, STDIN_FILENO);
		close(cmd->in->fd);
	}
	else
		dup2(pi.pe_prev, STDIN_FILENO);
	if (cmd->out != NULL && cmd->out->exists)
	{
		if (cmd->out->fd == -1)
			return (perror(cmd->out->name), 1);
		dup2(cmd->out->fd, STDOUT_FILENO);
		close(cmd->out->fd);
	}
	else
		dup2(pi.pe[1], STDOUT_FILENO);
	return (0);
}

void	child_process(t_exec *exec, int i)
{
	if (open_fd(&exec->cmd[i], exec->pi))
	{
		close_files(exec->files, exec->file_size);
		free_token(exec->allocated_content);
		exit(127);
	}
	close_files(exec->files, exec->file_size);
	close_pipe(&exec->pi, 0b111);
	if (is_builtin(exec->cmd[i].cmd))
		execute_builtin(exec, i);
	create_cmd(&exec->cmd[i], exec->env);
	free_token(exec->allocated_content);
	// execute_command(exec->cmd[i].cmd, exec->cmd[i].args, exec->env);
	execve(exec->cmd[i].cmd, exec->cmd[i].args, exec->env);
	ft_free_dstr(exec->env);
	exit(1);
}

/*
-> exec
	(tokens) (env)
	-> child frees (tokens) (env)
	~~~> alloc (cpy of args) free (tokens)
	~~~> alloc (split of PATH) ??? (x)	- lets try without it
										- otherwise we just allocate it
		-> exec frees (char **) (env)
*/
