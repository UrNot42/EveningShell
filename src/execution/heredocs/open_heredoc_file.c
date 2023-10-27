/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:05:19 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/27 19:05:34 by aoberon          ###   ########.fr       */
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

/**
 * @brief Create and open the file use for the heredoc.
 * 
 * @param fd_read fd to read the file, use later in the execution.
 * @param fd_write fd to write in the file, use to save the heredoc input.
 * @param filename name of the name to create and open.
 * Called .heredoc if the file doesn't exist,
 * the name is change if the file exist.
 * @return int return 1 if there is no error, 0 otherwise.
 */
int	open_heredoc(int *fd_read, int *fd_write, char *filename)
{
	int		i;
	char	str_itoa[10];

	i = 0;
	while (!access(filename, F_OK))
	{
		ft_itoa_no_malloc(i, str_itoa);
		filename = ft_strjoin("/tmp/.heredoc", str_itoa);
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
