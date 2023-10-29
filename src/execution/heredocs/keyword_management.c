/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyword_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:29:24 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/27 18:48:49 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_size_keyword(char *keyword)
{
	size_t	i;
	size_t	length;

	i = -1;
	length = 0;
	while ((keyword[++i]))
	{
		if (keyword[i] == '\'')
		{
			while (keyword[++i] != '\'')
				++length;
		}
		else if (keyword[i] == '"')
		{
			while (keyword[++i] != '"')
				++length;
		}
		else
			++length;
	}
	return (length);
}

static void	copy_keyword(char **new_keyword, char *keyword, size_t length)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j <= length)
	{
		if (keyword[i] == '\'')
		{
			++i;
			while (keyword[i] != '\'')
				(*new_keyword)[j++] = keyword[i++];
			++i;
		}
		else if (keyword[i] == '"')
		{
			++i;
			while (keyword[i] != '"')
				(*new_keyword)[j++] = keyword[i++];
			++i;
		}
		else
			(*new_keyword)[j++] = keyword[i++];
	}
}

char	*get_keyword(char *keyword)
{
	size_t	length;
	char	*new_keyword;

	length = get_size_keyword(keyword);
	new_keyword = ft_calloc(length + 1, sizeof(char));
	if (!new_keyword)
	{
		printf("Error of malloc.\n");
		return (NULL);
	}
	copy_keyword(&new_keyword, keyword, length);
	return (new_keyword);
}
