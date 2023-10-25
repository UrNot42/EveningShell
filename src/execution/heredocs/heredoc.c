/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:16:16 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/25 15:03:03 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("l : [%c] / b [%c]	|	l : [%zu] / b [%zu]\n", little_str[l], big_str[b], l, b);
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

int	heredoc(char *end_word)
{
	int		fd;
	int		end_bytes;
	char	*line;

	fd = open("file_heredoc", O_CREAT | O_WRONLY);
	end_bytes = 1;
	line = readline("heredoc>");
	while (end_bytes)
	{
		printf("%s\n", line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		if (ft_strcontains(line, end_word))
		{
			end_bytes = 0;
		}
		if (end_bytes)
			line = readline("heredoc>");
	}
	close(fd);
	return (0);
}
