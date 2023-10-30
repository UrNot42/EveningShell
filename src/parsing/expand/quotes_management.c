/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:48:55 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/30 20:51:14 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_size_word(char *word)
{
	size_t	i;
	size_t	length;

	i = -1;
	length = 0;
	while ((word[++i]))
	{
		if (word[i] == '\'')
		{
			while (word[++i] != '\'')
				++length;
		}
		else if (word[i] == '"')
		{
			while (word[++i] != '"')
				++length;
		}
		else
			++length;
	}
	return (length);
}

static void	copy_word(char **new_word, char *word, size_t length)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j <= length)
	{
		if (word[i] == '\'')
		{
			++i;
			while (word[i] != '\'')
				(*new_word)[j++] = word[i++];
			++i;
		}
		else if (word[i] == '"')
		{
			++i;
			while (word[i] != '"')
				(*new_word)[j++] = word[i++];
			++i;
		}
		else
			(*new_word)[j++] = word[i++];
	}
}

char	*remove_quotes(char *word)
{
	size_t	length;
	char	*new_word;

	length = get_size_word(word);
	new_word = ft_calloc(length + 1, sizeof(char));
	if (!new_word)
		return (NULL);
	copy_word(&new_word, word, length);
	return (new_word);
}
