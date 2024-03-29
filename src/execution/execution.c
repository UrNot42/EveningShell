/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:31:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/18 12:46:30 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	finish_execute(t_exec *exec)
{
	int	error_code;

	error_code = wait_pids(exec->pi.ds);
	signal(SIGINT, sig_handler_prompt);
	signal(SIGQUIT, SIG_IGN);
	free_exec(exec, false);
	return (error_code);
}

void	start_cmd(t_exec *exec, int i, int last_err)
{
	exec->pi.ds[i] = fork();
	if (exec->pi.ds[i] == 0)
		child_process(exec, i, last_err);
}

int	run_one_builtin(t_exec *exec, int last_err)
{
	int	code;
	int	fd;

	fd = dup(STDOUT_FILENO);
	if (fd == -1)
		return (error_dup_failed("single stdout"), 2);
	if (dup_fd(&exec->cmd[0], exec->pi))
		code = 1;
	else
		code = execute_builtin(exec, last_err, 0, fd);
	close_files(exec->files, exec->file_size);
	free_exec(exec, false);
	if (dup2(fd, STDOUT_FILENO) == -1)
		error_dup_failed("single out stdout");
	close(fd);
	return (code);
}

int	execute(t_compound *elemt_list, char ***env, int last_err)
{
	t_exec	exec;
	int		i;

	if (set_execute_struct(elemt_list, &exec, env))
		return (1);
	if (open_here_documents(exec.files, &exec))
		return (free_exec(&exec, false), g_signal);
	open_files(exec.files);
	if (exec.pipe_size == 0 && is_builtin(exec.cmd[0].cmd))
		return (run_one_builtin(&exec, last_err));
	signal(SIGINT, SIG_IGN);
	i = 0;
	while (i < exec.cmd_size)
	{
		if (i < exec.pipe_size)
			pipe(exec.pi.pe);
		start_cmd(&exec, i, last_err);
		close_pipe(&exec.pi, PIP_PREV);
		exec.pi.pe_prev = exec.pi.pe[0];
		close_pipe(&exec.pi, PIP_ONE);
		i++;
	}
	close_pipe(&exec.pi, PIP_READ);
	return (close_files(exec.files, exec.file_size), finish_execute(&exec));
}
