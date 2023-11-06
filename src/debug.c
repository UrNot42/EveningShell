/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:16:01 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/06 17:41:49 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_double_char(char **argv, char *debug_print, int print_name)
{
	int	i;

	if (print_name)
		printf("\n-- %s --\n", debug_print);
	i = 0;
	while (argv[i])
	{
		printf("%s[%d] : `%s`\n", debug_print, i, argv[i]);
		++i;
	}
}

void	debug_compound(t_compound *compound, char *debug_print)
{
	int	i;

	printf("\n-- %s --\n", debug_print);
	i = 0;
	while (compound[i].type != UNSET && compound[i].type != -1)
	{
		if (compound[i].type == CMD)
			printf("compound[%d] type : CMD\n", i);
		if (compound[i].type == REDIR_IN)
			printf("compound[%d] type : REDIR_IN\n", i);
		if (compound[i].type == REDIR_OUT)
			printf("compound[%d] type : REDIR_OUT\n", i);
		if (compound[i].type == HERE_DOC)
			printf("compound[%d] type : HERE_DOC\n", i);
		if (compound[i].type == APPEND)
			printf("compound[%d] type : APPEND\n", i);
		if (compound[i].type == PIPE)
			printf("compound[%d] type : PIPE\n", i);
		debug_double_char(compound[i].content, "	content", 0);
		++i;
	}
}

void	debug_heredoc(int fd)
{
	ssize_t	read_size;
	char	buffer[11];

	read_size = read(fd, &buffer, 10);
	buffer[read_size] = '\0';
	printf("-- HEREDOC - FD [%d] -- \n", fd);
	while (read_size && ft_strchr(buffer, '\n'))
	{
		printf("%s", buffer);
		read_size = read(fd, &buffer, 10);
		buffer[read_size] = '\0';
	}
}
