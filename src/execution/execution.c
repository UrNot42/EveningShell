/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:31:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/24 18:50:43 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: actually code the function please
// int	execute(t_token *token_list, char **env)
// {
// 	int		i;
// 	t_pipes	my_pipe;

// 	i = 0;
// 	while (token_list && token_list[i])
// 	{
// 		if () // not last cmd
// 			pipe(my_pipe.s);
// 		pipex.pids[i] = fork(); // store the pid
// 		if (pipex.pids[i] == 0) // if inside the child do the process
// 			child_process(&pipex, av[2 + i], i); // start the child loop
// 		if (pipex.prev_pipe != -1) // if there is a previous pipe close it
// 			close(pipex.prev_pipe);
// 		pipex.prev_pipe = pipex.zelda[0]; // store the new previous pipe for the next child process to use
// 		close(pipex.zelda[1]);
// 		i++;
// 	}
// 	(close(pipex.zelda[0]), close(pipex.prev_pipe)); // close ur unclosed pipes
// 	free_dstr(pipex.path);
// 	pipex.pids[i] = -1;
// 	return (wait_pids(pipex.pids));
// }
/*
int	wait_pids(int *pids)
{
	int	i;
	int	status;

	i = 0;
	while (pids[i] != -1)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}*/
