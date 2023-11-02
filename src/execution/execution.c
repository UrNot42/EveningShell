/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:31:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/02 16:41:47 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	finish_execute(t_exec *exec)
{
	int	error_code;

	error_code = wait_pids(exec->pi.ds);
	free_exec(exec, false);
	return (error_code);
}

void	start_cmd(t_exec *exec, int i, int last_err)
{
	if (is_builtin(exec->cmd[i].cmd) && exec->cmd_size == 1)
	{
		dup_fd(&exec->cmd[i], exec->pi);
		execute_builtin(exec, i, last_err);
	}
	else
	{
		exec->pi.ds[i] = fork();
		if (exec->pi.ds[i] == 0)
			child_process(exec, i, last_err);
	}
}

int	execute(t_compound *elemt_list, char **env, int last_err)
{
	t_exec	exec;
	int		i;

	if (set_execute_struct(elemt_list, &exec, env))
		return (1);
	open_here_documents(exec.files, &exec);
	open_files(exec.files);
	i = 0;
	while (i < exec.cmd_size)
	{
		if (i < exec.cmd_size - 1)
			pipe(exec.pi.pe);
		start_cmd(&exec, i, last_err);
		close_pipe(&exec.pi, PIP_PREV);
		exec.pi.pe_prev = exec.pi.pe[0];
		close_pipe(&exec.pi, PIP_ONE);
		i++;
	}
	close_pipe(&exec.pi, PIP_READ);
	exec.pi.ds[i] = -1;
	return (finish_execute(&exec));
}
