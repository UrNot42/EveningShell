/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:01:47 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/01 15:20:59 by aoberon          ###   ########.fr       */
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
		if (!src[i])
			break ;
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (free(dest), NULL);
		i++;
	}
	return (dest);
}

/**
 * @brief Create a compound
 * 
 * @param argv array of strings used to create the compound
 * @param type type of the compound (CMD, REDIR_IN, REDIR_OUT, HERE_DOC, APPEND,
 * PIPE)
 * @param size size of the compound (number of strings in the compound)
 * @return t_compound compound created
 */
t_compound	create_compound(char **argv, int type, int size)
{
	t_compound	compound;

	compound.type = type;
	compound.content = doublecharncpy(argv, size);
	return (compound);
}
