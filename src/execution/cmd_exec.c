/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:47:21 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/30 09:18:42 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (cmd->in != NULL && cmd->out->exists)
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
/*
char	*build_cmd(char *path, char *cmd)
{
	char	*full_cmd;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	full_cmd = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_cmd)
		return (NULL);
	return (full_cmd);
}

char	*find_path(char **possible_path, char *cmd)
{
	char	*tmp;
	int		i;

	if (!access(cmd, F_OK | X_OK))
		return (ft_strdup(cmd));
	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '/')
			return (write(2, cmd, ft_strlen(cmd)),
				write(2, ": No such file or directory\n", 28), NULL);
		i++;
	}
	i = 0;
	while (possible_path && possible_path[i])
	{
		tmp = build_cmd(possible_path[i], cmd);
		if (tmp && !access(tmp, F_OK | X_OK))
			return (tmp);
		if (tmp)
			free(tmp);
		i++;
	}
	return (write(2, "Command '", 9), write(2, cmd, ft_strlen(cmd)),
		write(2, "' not found\n", 12), NULL);
}

char	**build_argv(t_pipex *pipex)
{
	int		nb_word;
	char	**argv;

	nb_word = 1;
	while (pipex->cmd.cmd[nb_word])
		nb_word++;
	argv = ft_calloc(nb_word + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(pipex->cmd.path);
	if (!(argv[0]))
		return (free_dstr(argv), NULL);
	nb_word = 1;
	while (pipex->cmd.cmd[nb_word])
	{
		argv[nb_word] = ft_strdup(pipex->cmd.cmd[nb_word]);
		if (!argv[nb_word])
			return (free_dstr(argv), NULL);
		nb_word++;
	}
	free_dstr(pipex->cmd.cmd);
	pipex->cmd.cmd = argv;
	return (argv);
}*/

void	child_process(t_exec *exec, int i)
{
	printf("Inside the child\n");
	if (open_fd(&exec->cmd[i], exec->pi))
	{
		close_files(exec->files, exec->file_size);
		free_token(exec->allocated_content);
		exit(127);
	}
	close_files(exec->files, exec->file_size);
	close_pipe(&exec->pi, 0b111);
	execve(exec->cmd[i].cmd, exec->cmd[i].args, exec->env);
	exit(1);
}

/*
-> exec
	(tokens) (env)
	-> child
*/
