/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:15:05 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/21 23:18:20 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief joins a path with a command
 * ex:
 *  ls with /bin
 * gives
 *  /bin/ls
 *
 * @param cmd
 * @param path
 * @param size
 * @return char*
 */
char	*build_cmd(char *cmd, char *path, int size)
{
	char	*full_cmd;
	char	*temp;
	int		full_size;

	temp = ft_strjoin("/", cmd);
	if (!temp)
		return (NULL);
	full_size = ft_strlen(temp) + size + 1;
	full_cmd = ft_calloc(full_size, sizeof(char));
	if (!full_cmd)
		return (free(temp), NULL);
	ft_strlcpy(full_cmd, path, size + 1);
	ft_strlcat(full_cmd, temp, full_size);
	free(temp);
	return (full_cmd);
}

int	find_path_size(char *path)
{
	int	size;

	size = 0;
	while (path[size] != ':' && path[size] != '\n' && path[size] != '\0')
		size++;
	return (size);
}

bool	is_directory(char *path)
{
	int	fd;
	int	i;
	int	try;

	i = 0;
	try = false;
	while (path && path[i])
		if (path[i++] == '/')
			try = true;
	if (!try)
		return (false);
	fd = open(path, O_DIRECTORY);
	if (fd == -1)
		return (false);
	write(2, path, ft_strlen(path));
	write(2, ": Is a directory\n", 17);
	close(fd);
	return (true);
}

/**
 * @brief Get the cmd object with its correct path
 *
 * @param cmd
 * @param path
 * @param err
 * @return char*
 */
char	*get_cmd(char *cmd, char *path, int *err)
{
	char	*tmp;
	int		i;

	if (is_directory(cmd))
		return (++*err, NULL);
	i = 0;
	while (cmd && cmd[i])
	{
		if ((cmd[i] == '/' || !path) && !access(cmd, F_OK | X_OK))
			return (ft_strdup(cmd));
		if ((cmd[i++] == '/' || !path) && access(cmd, F_OK | X_OK))
			return (perror(cmd), (access(cmd, X_OK) && ++*err),
				(access(cmd, F_OK) && --*err), NULL);
	}
	while (path && *path)
	{
		i = find_path_size(path);
		tmp = build_cmd(cmd, path, i);
		if (tmp && !access(tmp, F_OK | X_OK))
			return (tmp);
		if (tmp)
			free(tmp);
		path += i + (path[i] != '\0');
	}
	return (command_not_found(cmd, false), NULL);
}

/**
 * @brief Create a cmd object
 *  and sets the given adresses of char *cmd and char **args to a new allocated
 *  address
 *
 * @param cmd
 * @param env
 * @param n_cmd
 * @param n_args
 * @return int
 */
int	create_cmd(t_cmd *cmd, char **env, char **n_cmd, char ***n_args)
{
	char	*env_path;
	int		index;
	int		err;

	err = 0;
	if (!cmd->cmd)
		return (1);
	if (*cmd->cmd == '\0')
		return (command_not_found("", false), 1);
	index = get_env_var_index(env, "PATH");
	if (index != -1)
		env_path = &env[index][5];
	else
		env_path = NULL;
	(*n_args) = ft_dstrdup((const char **)cmd->args);
	if (!(*n_args))
		return (1);
	(*n_cmd) = get_cmd(cmd->cmd, env_path, &err);
	if (!(*n_cmd))
		return (ft_free_dstr((*n_args)), 1 + err);
	if (is_directory(*n_cmd))
		return (ft_free_dstr((*n_args)), free(*n_cmd), 2);
	if (ft_strcmp((*n_cmd), (*n_args)[0]))
		(free((*n_args)[0]), (*n_args)[0] = (*n_cmd));
	return (0);
}
