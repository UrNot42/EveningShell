/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:31:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/02 09:15:21 by ulevallo         ###   ########.fr       */
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

int	execute(t_compound *elemt_list, char **env)
{
	t_exec	exec;
	int		i;

	if (set_execute_struct(elemt_list, &exec, env))
		return (1);
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
	exec.pi.ds[i] = -1;
	return (finish_execute(&exec));
}
