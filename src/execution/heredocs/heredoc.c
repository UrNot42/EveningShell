/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:16:16 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/26 17:09:50 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_nbrlen(int n)
{
	if (n < 0)
		n = -n;
	if (n < 10)
		return (1);
	return (1 + ft_nbrlen(n / 10));
}

/**
 * @brief Converts an integer to a string without malloc.
 * 
 * @param n integer to convert.
 * @param result string to store the result.
 */
static void	ft_itoa_no_malloc(int n, char result[10])
{
	unsigned int	tmp;
	size_t			size;

	if (n < 0)
		tmp = -n;
	else
		tmp = n;
	size = (ft_nbrlen(tmp) + (n < 0));
	ft_bzero(result, 10);
	result[size--] = '\0';
	if (n == 0)
		result[0] = '0';
	while (tmp > 0)
	{
		result[size] = (tmp % 10) + '0';
		tmp /= 10;
		size--;
	}
	if (n < 0)
		result[0] = '-';
}


static int	ft_strcontains(char *big_str, char *little_str)
{
	size_t	b;
	size_t	l;
	size_t	size_little;

	size_little = ft_strlen(little_str);
	if (!big_str || !little_str || (ft_strlen(big_str) < size_little))
		return (0);
	b = 0;
	l = 0;
	while (big_str[b])
	{
		// printf("l : [%c] / b [%c]	|	l : [%zu] / b [%zu]\n", little_str[l], big_str[b], l, b);
		if (little_str[l] == big_str[b])
		{
			l++;
			if (l == size_little)
				return (1);
		}
		else
			l = 0;
		b++;
	}
	return (0);
}

int	open_heredoc(int *fd_read, int *fd_write, char *filename)
{
	int		i;
	char	str_itoa[10];

	i = 0;
	while (!access(filename, F_OK))
	{
		ft_itoa_no_malloc(i, str_itoa);
		filename = ft_strjoin(".heredoc", str_itoa);
		if (!filename)
			return (printf("Error of malloc.\n"), 0);
		++i;
	}
	*fd_write = open(filename, O_CREAT | O_WRONLY);
	if (*fd_write == -1)
		return (printf("protect fd_write !\n"), 0);
	*fd_read = open(filename, O_RDONLY);
	if (*fd_read == -1)
		return (printf("protect fd_read !\n"), 0);
	unlink(filename);
	return (1);
}

void	create_heredoc(int fd_write, char *end_word)
{
	int		end_bytes;
	char	*line;

	end_bytes = 1;
	line = readline(">");
	while (end_bytes)
	{
		// printf("%s\n", line);
		write(fd_write, line, ft_strlen(line));
		if (ft_strcontains(line, end_word))
		{
			end_bytes = 0;
		}
		if (end_bytes)
		{
			write(fd_write, "\n", 1);
			line = readline(">");
		}
	}
	close(fd_write);
}

int	heredoc(char *end_word)
{
	int		fd_read;
	int		fd_write;

	if (!open_heredoc(&fd_read, &fd_write, ".heredoc"))
		return (-1);
	create_heredoc(fd_write, end_word);
	return (fd_read);
}
