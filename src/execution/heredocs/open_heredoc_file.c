/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:05:19 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/01 18:24:59 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get a length of a number.
 * 
 * @param n number to get the length.
 * @return int return the length.
 */
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

int	open_heredoc_read(char **filename, char *filename_std)
{
	int		i;
	char	str_itoa[10];
	int		fd_read;

	i = 0;
	*filename = NULL;
	while (!access(filename_std, F_OK))
	{
		ft_itoa_no_malloc(i, str_itoa);
		*filename = ft_strjoin(filename_std, str_itoa);
		printf("filename = %s\n", *filename);
		if (!*filename)
			return (printf("Error of malloc.\n"), -42);
		++i;
	}
	if (*filename == NULL)
		*filename = ft_strdup(filename_std);
	fd_read = open(*filename, O_CREAT | O_RDONLY, 0666);
	if (fd_read == -1)
		return (printf("protect fd_read !\n"), -1);
	return (fd_read);
}

int	open_heredoc_write(char *filename)
{
	int	fd_write;

	fd_write = open(filename, O_WRONLY);
	if (fd_write == -1)
		return (printf("protect fd_write !\n"), -1);
	unlink(filename);
	free(filename);
	return (fd_write);
}
