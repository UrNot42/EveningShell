/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:15:05 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/31 17:46:08 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_cmd(char *cmd, char *path)
{
	char	*tmp;
	int		i;

	if (!access(cmd, F_OK | X_OK))
		return (ft_strdup(cmd));
	i = 0;
	while (cmd && cmd[i])
		if (cmd[i++] == '/')
			return (write(2, cmd, ft_strlen(cmd)),
				write(2, ": No such file or directory\n", 28), NULL);
	i = 0;
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
	return (write(2, "Command '", 9), write(2, cmd, ft_strlen(cmd)),
		write(2, "' not found\n", 12), NULL);
}

int	create_cmd(t_cmd *cmd, char **env, char **n_cmd, char ***n_args)
{
	char	*env_path;
	int		index;

	index = get_env_var_index(env, "PATH");
	if (index != -1)
		env_path = &env[index][5];
	else
		env_path = NULL;
	(*n_args) = ft_dstrdup((const char **)cmd->args);
	if (!(*n_args))
		return (1);
	(*n_cmd) = get_cmd(cmd->cmd, env_path);
	if (!(*n_cmd))
		return (ft_free_dstr((*n_args)), 1);
	if (ft_strcmp((*n_cmd), (*n_args)[0]))
	{
		free((*n_args)[0]);
		(*n_args)[0] = (*n_cmd);
	}
	return (0);
}
