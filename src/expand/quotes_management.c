/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:48:55 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/15 16:53:08 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the word contains a double or single quote
 * 
 * @param word char * word to check
 * @return true if the word contains a double or single quote
 * @return false if not
 */
static bool	is_quotes(char *word)
{
	size_t	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '"' || word[i] == '\'')
			return (true);
		++i;
	}
	return (false);
}

/**
 * @brief Get the size of the new_word, meaning the size of the word without
 *  (depending on the rules of bash)
 * 
 * @param word char * word to get the size
 * @return size_t size of the new_word
 */
static size_t	get_size_new_word(char *word)
{
	size_t	i;
	size_t	length;

	i = -1;
	length = 0;
	while ((word[++i]))
	{
		if (word[i] == '\'')
		{
			while (word[i] && word[++i] != '\'')
				++length;
		}
		else if (word[i] == '"')
		{
			while (word[i] && word[++i] != '"')
				++length;
		}
		else
			++length;
	}
	return (length);
}

/**
 * @brief Copy the word without the quotes (depending on the rules of bash)
 * in the new_word
 * 
 * @param new_word char ** new word without quotes
 * @param word char * word to copy
 * @param length size_t length of the new_word
 */
static void	copy_word(char **new_word, char *word, size_t length)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j <= length)
	{
		if (word[i] && word[i] == '\'')
		{
			++i;
			while (word[i] && word[i] != '\'')
				(*new_word)[j++] = word[i++];
			++i;
		}
		else if (word[i] && word[i] == '"')
		{
			++i;
			while (word[i] && word[i] != '"')
				(*new_word)[j++] = word[i++];
			++i;
		}
		else
			(*new_word)[j++] = word[i++];
	}
}

/**
 * @brief Create a new word without quotes (following the rules of bash)
 * 
 * @param word char * word to remove quotes in
 * @return char* new word without quotes
 */
char	*remove_quotes(char *word)
{
	size_t	length;
	char	*new_word;

	if (!is_quotes(word))
		return (word);
	length = get_size_new_word(word);
	new_word = ft_calloc(length + 1, sizeof(char));
	if (!new_word)
		return (NULL);
	copy_word(&new_word, word, length);
	free(word);
	return (new_word);
}
