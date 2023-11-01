/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:06:23 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/01 18:32:59 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_file(t_compound *token, t_file *file, int max_file)
{
	size_t	i;
	int		f;

	i = 0;
	f = 0;
	while (token[i].content && f < max_file)
	{
		if (token[i].type == REDIR_IN || token[i].type == REDIR_OUT
			|| token[i].type == APPEND || token[i].type == HERE_DOC)
		{
			file[f].exists = true;
			file[f].type = token[i].type;
			file[f].fd = -1;
			file[f].name = token[i].content[1];
			f++;
		}
		i++;
	}
	return (0);
}

int	open_files(t_file *file)
{
	int	i;

	i = 0;
	while (file[i].name)
	{
		if (file[i].type == REDIR_OUT)
			file[i].fd = open(file[i].name, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		else if (file[i].type == APPEND)
			file[i].fd = open(file[i].name, O_APPEND | O_CREAT | O_WRONLY, 0666);
		else if (file[i].type == REDIR_IN)
			file[i].fd = open(file[i].name, O_RDONLY);
		else if (file[i].type == HERE_DOC)
			// file[i].fd = heredoc(exec, file[i].name);
		if (file[i].fd == -1)
		{
			close_files(file, i);
			return (perror(file[i].name), i);
		}
		i++;
	}
	return (0);
}

void	close_files(t_file *file, int to)
{
	int	i;

	// printf("closed_files\n");
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

/*
Here is a prototype which copies memory so that we're independant from tokens
int	dup_file_names(t_files *file, int max_file)
{
	int	i;

	i = 0;
	while (i < max_file)
	{
		file[i].name = ft_strdup(file[i].name);
		if (!file[i].name)
			return (free_files(file), 1);
		file[i].exists = true;
		i++;
	}
	return (0);
}
*/
