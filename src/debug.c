/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:16:01 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/26 17:10:14 by aoberon          ###   ########.fr       */
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
		printf("%s[%d] : %s\n", debug_print, i, argv[i]);
		++i;
	}
}

void	debug_token(t_token *token, char *debug_print)
{
	int	i;

	printf("\n-- %s --\n", debug_print);
	i = 0;
	while (token[i].type != -1)
	{
		if (token[i].type == 0)
			printf("token[%d] type : CMD\n", i);
		if (token[i].type == 1)
			printf("token[%d] type : REDIR_IN\n", i);
		if (token[i].type == 2)
			printf("token[%d] type : REDIR_OUT\n", i);
		if (token[i].type == 3)
			printf("token[%d] type : HERE_DOC\n", i);
		if (token[i].type == 4)
			printf("token[%d] type : APPEND\n", i);
		if (token[i].type == 5)
			printf("token[%d] type : PIPE\n", i);
		debug_double_char(token[i].content, "	content", 0);
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
