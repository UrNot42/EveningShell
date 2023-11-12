/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:05:19 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 15:44:59 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_heredoc_read(char **filename, char *filename_std)
{
	int		i;
	char	str_itoa[12];
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
