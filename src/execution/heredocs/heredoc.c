/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:16:16 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/30 13:49:15 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a heredoc.
 * 
 * @param fd_write fd to write in the file, use to save the heredoc input.
 * @param keyword char * use to stop the heredoc if the input is equal.
 */
static void	create_heredoc(int fd_write, char *keyword)
{
	char	*line;

	line = readline(">");
	while (1)
	{
		write(fd_write, line, ft_strlen(line));
		if (!ft_strcmp(line, keyword))
			break ;
		write(fd_write, "\n", 1);
		line = readline(">");
	}
	close(fd_write);
}

/**
 * @brief Heredoc execution.
 * 
 * @param keyword char * use to stop the heredoc if the input is equal.
 * @return int Return the fd to read the file, use later in the execution.
 * Return -1 if there is an error.
 */
int	heredoc(char *keyword)
{
	int		fd_read;
	int		fd_write;

	if (!open_heredoc(&fd_read, &fd_write, "/tmp/.heredoc"))
		return (-1);
	create_heredoc(fd_write, keyword);
	return (fd_read);
}
