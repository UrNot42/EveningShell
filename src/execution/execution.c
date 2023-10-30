/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:31:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/30 10:53:00 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_token *token_list, char **env)
{
	t_exec	exec;
	int		i;

	if (set_execute_struct(token_list, &exec, env))
		return (1);
	// print_exec_sruct(&exec);
	open_files(exec.files);
	i = 0;
	while (i < exec.cmd_size)
	{
		if (i < exec.cmd_size - 1)
			pipe(exec.pi.pe);
		exec.pi.ds[i] = fork();
		if (exec.pi.ds[i] == 0)
			child_process(&exec, i);
		close_pipe(&exec.pi, 0b100);
		exec.pi.pe_prev = exec.pi.pe[0];
		close_pipe(&exec.pi, 0b010);
		i++;
	}
	close_pipe(&exec.pi, 0b101);
	free_token(token_list);
	exec.pi.ds[i] = -1;
	return (wait_pids(exec.pi.ds));
}

/*
commented version of the code

int	execute(t_token *token_list, char **env)
{
	t_exec	exec;
	int		i;

	if (set_execute_struct(token_list, &exec, env))
		return (1);
	open_files(exec.files);
	i = 0;
	while (i < exec.cmd_size)
	{
		if (i < exec.cmd_size - 1) // not last cmd
			pipe(exec.pi.pe);
		exec.pi.ds[i] = fork(); // store the pid
		if (exec.pi.ds[i] == 0) // if inside the child do the process
			child_process(&exec, i); // start the child loop
		if (exec.pi.pe_prev != -1) // if there is a previous pipe close it
			close(exec.pi.pe_prev);
		exec.pi.pe_prev = exec.pi.pe[0]; // store the new previous pipe for the next child process to use
		if (exec.pi.pe[1] != -1)
			close(exec.pi.pe[1]);
		i++;
	}
	(close(exec.pi.pe[0]), close(exec.pi.pe_prev)); // close ur unclosed pipes
	free_token(token_list);
	exec.pi.ds[i] = -1;
	return (wait_pids(exec.pi.ds));
}
*/
