/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:16:16 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 12:44:29 by aoberon          ###   ########.fr       */
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
			printf("MarmiShell-4.2$: warning: here-document delimited by end-of-file\
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

/**
 * @brief Free the keyword and close the fd if the assignment is false.
 * 	Else, save the keyword and the fd_write.
 * 
 * @param assignment bool to know if it has to save or free.
 * @param keyword char ** pointer of the keyword;
 * @param fd_write int * pointer of the fd_write.
 */
void	exit_heredoc(bool assignment, char **keyword, int *fd_write)
{
	static char		**static_keyword = NULL;
	static int		*static_fd_write = NULL;

	if (assignment == true)
	{
		static_keyword = keyword;
		static_fd_write = fd_write;
	}
	if (assignment == false)
	{
		free(*static_keyword);
		close(*static_fd_write);
	}
}

/**
 * @brief Do the process of the child of the heredoc.
 * 	Meaning, open the file to write in it.
 * 
 * @param exec t_exec struct.
 * @param keyword char * use to stop the heredoc if the input is equal.
 * @param filename char * filename to open.
 * @param fd_read in fd of the read to close.
 */
void	heredoc_child(t_exec *exec, char *keyword, char *filename, int fd_read)
{
	int					fd_write;
	char				*keyword_copy;

	close(fd_read);
	keyword_copy = ft_strdup(keyword);
	close_files(exec->files, exec->file_size);
	free_exec(exec, 1);
	if (!keyword_copy)
		exit(-42);
	exit_heredoc(true, &keyword_copy, &fd_write);
	signal(SIGINT, sig_handler_heredoc);
	fd_write = open_heredoc_write(filename);
	if (fd_write == -1)
	{
		free(keyword_copy);
		exit (-1);
	}
	create_heredoc(fd_write, keyword_copy);
	free(keyword_copy);
	exit(0);
}

/**
 * @brief Process of the heredoc.
 * 
 * @param exec t_exec struct.
 * @param keyword char * use to stop the heredoc if the input is equal.
 * @return int the fd of the read, or -1 if error of open,
 * -42 if error of malloc, -43 if error of fork, -130 if error of ctrl + c.
 */
int	heredoc(t_exec *exec, char *keyword)
{
	int					fd_read;
	int					fork_process;
	char				*filename;
	int					fork_status;

	signal(SIGINT, SIG_IGN);
	fd_read = open_heredoc_read(&filename, "/tmp/.heredoc");
	if (fd_read == -1)
		return (-1);
	if (fd_read == -42)
		return (-42);
	fork_process = fork();
	if (fork_process == -1)
		return (free(filename), printf("MarmiShell-4.2$: fork failed\n"), -43);
	if (fork_process == 0)
	{
		heredoc_child(exec, keyword, filename, fd_read);
	}
	waitpid(fork_process, &fork_status, 0);
	free(filename);
	if (WIFEXITED(fork_status) && WEXITSTATUS(fork_status) == 130)
		return (close (fd_read), -130);
	return (fd_read);
}
