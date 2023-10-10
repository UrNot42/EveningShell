/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:01:47 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/10 16:27:41 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Copies an array of strings, limited by n
 * 
 * @param src array of strings to be copied
 * @param n limit of the copy
 * @return char** array of strings copied
 */
char	**doublecharncpy(char **src, size_t n)
{
	char	**dest;
	size_t	i;

	dest = ft_calloc(n + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (printf("FREE AND EXIT !\n"), NULL);
		i++;
	}
	return (dest);
}

/**
 * @brief Create a token
 * 
 * @param argv array of strings used to create the token
 * @param type type of the token (CMD, REDIR_IN, REDIR_OUT, HERE_DOC, APPEND,
 * PIPE)
 * @param size size of the token (number of strings in the token)
 * @return t_token token created
 */
t_token	create_token(char **argv, int type, int size)
{
	t_token	token;

	token.type = type;
	token.content = doublecharncpy(argv, size);
	if (!token.content)
		return (printf("FREE AND EXIT !\n"), token);
	return (token);
}
