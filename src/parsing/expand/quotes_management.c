/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:48:55 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/31 13:10:48 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quotes(char *word)
{
	size_t	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '"' || word[i] == '\'')
			return (1);
		++i;
	}
	return (0);
}

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

	if (!is_quotes(word))
		return (word);
	length = get_size_word(word);
	new_word = ft_calloc(length + 1, sizeof(char));
	if (!new_word)
		return (NULL);
	copy_word(&new_word, word, length);
	free(word);
	return (new_word);
}
