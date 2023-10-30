/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:47:21 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/30 11:09:11 by ulevallo         ###   ########.fr       */
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
	// execute_command(exec->cmd[i].cmd, exec->cmd[i].args, exec->env);
	execve(exec->cmd[i].cmd, exec->cmd[i].args, exec->env);
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
