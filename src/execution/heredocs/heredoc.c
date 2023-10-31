/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:16:16 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/31 15:20:13 by aoberon          ###   ########.fr       */
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

	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, keyword))
		{
			if (line)
				write(fd_write, "\0", 1);
			free(line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
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
	int		fork_process;

	signal(SIGINT, SIG_IGN);
	fork_process = fork();
	if (fork_process == -1)
		printf("Protector fork\n");
	if (fork_process == 0)
	{
		signal(SIGINT, sig_handler_heredoc);
		if (!open_heredoc(&fd_read, &fd_write, "/tmp/.heredoc"))
			return (-1);
		create_heredoc(fd_write, keyword);
	}
	waitpid(fork_process, &fd_read, 0);
	signal(SIGINT, sig_handler_neutral);
	return (fd_read);
}
