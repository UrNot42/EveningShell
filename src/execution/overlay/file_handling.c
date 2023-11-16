/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:06:23 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 13:15:24 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief fills the t_file list with corresponding type and values
 *
 * @param element
 * @param file
 * @param max_file
 * @return int
 */
int	fill_file(t_compound *element, t_file *file, int max_file)
{
	size_t	i;
	int		f;

	i = 0;
	f = 0;
	while (element[i].content && f < max_file)
	{
		if (element[i].type == REDIR_IN || element[i].type == REDIR_OUT
			|| element[i].type == APPEND || element[i].type == HERE_DOC)
		{
			file[f].exists = true;
			file[f].type = element[i].type;
			file[f].fd = -1;
			file[f].name = element[i].content[1];
			f++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief opens here documents and allows for stop by ctrl-C stopping everything
 *
 * @param file
 * @param exec
 * @return int
 */
int	open_here_documents(t_file *file, t_exec *exec)
{
	int	i;

	i = 0;
	while (file[i].name)
	{
		if (file[i].type == HERE_DOC)
			file[i].fd = heredoc(exec, file[i].name);
		if (file[i].type == HERE_DOC && file[i].fd < 0)
		{
			i = file[i].fd;
			if (i == -130)
				return (close_files(file, i), g_signal = 130, 130);
			else if (i == -42)
				i = 1;
			close_files(file, i);
			return (error_malloc_failed(false), i);
		}
		i++;
	}
	return (0);
}

/**
 * @brief opens every file
 *
 * @param file
 * @return int
 */
int	open_files(t_file *file)
{
	int	i;

	i = 0;
	while (file[i].name)
	{
		if (file[i].type == REDIR_OUT)
			file[i].fd = open(file[i].name, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		else if (file[i].type == APPEND)
			file[i].fd = open(file[i].name,
					O_APPEND | O_CREAT | O_WRONLY, 0666);
		else if (file[i].type == REDIR_IN)
			file[i].fd = open(file[i].name, O_RDONLY);
		if (file[i].fd == -1)
		{
			close_files(file, i);
			return (perror(file[i].name), i);
		}
		i++;
	}
	return (0);
}

/**
 * @brief safely closes every file
 * until reaching the last one
 *
 * @param file
 * @param to
 */
void	close_files(t_file *file, int to)
{
	int	i;

	i = 0;
	while (i < to)
	{
		if (file[i].exists && file[i].fd != -1)
		{
			close(file[i].fd);
		}
		i++;
	}
}
