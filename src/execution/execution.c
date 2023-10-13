/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:31:47 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/13 21:44:21 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: actually code the function please
int	execute(t_token *tokens, char **env)
{
	int	i;

	(void)env;
	i = 0;
	while (tokens && i < 2)
	{
		i++;
	}
	return (1);
}

/**
 * @brief char	**get_env_path(char **env)
{
	int		i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], PATH, PATH_SIZE))
			return (ft_split(&env[i][5], PATH_ENV_SEPARATOR));
		i++;
	}
	return (NULL);
}

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
}

void	init_pipex(t_pipex *pipex, int ac, char **av, char **env)
{
	pipex->env = env;
	pipex->size = ac - 3;
	pipex->infile = av[1];
	pipex->outfile = av[ac - 1];
	pipex->path = get_env_path(env);
	pipex->prev_pipe = -1;
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	int		i;

	if (ac < 5 || ac > 1026)
		return (ft_printf("not [enough/too_many] arguments\n"), EXIT_FAILURE);
	init_pipex(&pipex, ac, av, env);
	i = 0;
	while (i < (ac - 3))
	{
		if (i < (ac - 4))
			pipe(pipex.zelda);
		pipex.pids[i] = fork();
		if (pipex.pids[i] == 0)
			child_process(&pipex, av[2 + i], i);
		if (pipex.prev_pipe != -1)
			close(pipex.prev_pipe);
		pipex.prev_pipe = pipex.zelda[0];
		close(pipex.zelda[1]);
		i++;
	}
	close(pipex.zelda[0]);
	close(pipex.prev_pipe);
	free_dstr(pipex.path);
	pipex.pids[i] = -1;
	return (wait_pids(pipex.pids));
}
 */
