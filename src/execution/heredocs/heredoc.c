/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:16:16 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/06 21:01:54 by ulevallo         ###   ########.fr       */
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
		if (!line)
		{
			printf("minishell: warning: here-document delimited by end-of-file\
 (wanted `%s')\n", keyword);
			break ;
		}
		if (!ft_strcmp(line, keyword))
		{
			free(line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
	close(fd_write);
}

void	exit_heredoc(bool assignment, char **keyword, int *fd_write)
{
	static char	**static_keyword = NULL;
	static int	*static_fd_write = NULL;

	if (assignment == 1)
	{
		static_keyword = keyword;
		static_fd_write = fd_write;
	}
	if (assignment == 0)
	{
		free(*static_keyword);
		close(*static_fd_write);
	}
}

void	heredoc_child(t_exec *exec, char *keyword, char *filename, int fd_read)
{
	int		fd_write;
	char	*keyword_copy;

	close(fd_read);
	keyword_copy = ft_strdup(keyword);
	free_exec(exec, 1);
	if (!keyword_copy)
		exit(-42);
	exit_heredoc(1, &keyword_copy, &fd_write);
	signal(SIGINT, sig_handler_heredoc);
	fd_write = open_heredoc_write(filename);
	if (fd_write == -1)
	{
		free(keyword_copy);
		exit (-42);
	}
	create_heredoc(fd_write, keyword_copy);
	free(keyword_copy);
	exit(0);
}

int	heredoc(t_exec *exec, char *keyword)
{
	int		fd_read;
	int		fork_process;
	char	*filename;

	signal(SIGINT, SIG_IGN);
	fd_read = open_heredoc_read(&filename, "/tmp/.heredoc");
	fork_process = fork();
	if (fork_process == -1)
		printf("Protector fork\n");
	if (fork_process == 0)
	{
		heredoc_child(exec, keyword, filename, fd_read);
	}
	waitpid(fork_process, NULL, 0);
	free(filename);
	signal(SIGINT, sig_handler_prompt);
	return (fd_read);
}
