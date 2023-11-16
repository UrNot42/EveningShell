/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expand_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 21:34:33 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 09:49:13 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Go to the next single quote and if the single quote is the last char
 * 
 * @param word char * word to check
 * @param i int * index of the word
 * @return true if the word is not finished
 * @return false if the word is finished
 */
static bool	is_expand_dollar_single_quote(char *word, int *i)
{
	*i += 1;
	while (word[*i] && word[*i] != '\'')
		*i += 1;
	if (!word[*i])
		return (false);
	return (true);
}

/**
 * @brief Goes the next double quote and check if there is a dollar to expand
 * 
 * @param word char * word to check
 * @param i int * index of the word
 * @return true if the word contains a dollar to expand
 *  or if the word is not finished
 * @return false if the word is finished and does not contain a dollar to expand
 */
static bool	is_expand_dollar_double_quote(char *word, int *i)
{
	*i += 1;
	while (word[*i] && word[*i] != '"')
	{
		if (word[*i] == '$')
			return (true);
		*i += 1;
	}
	if (!word[*i])
		return (false);
	return (true);
}

/**
 * @brief Check if the word contains a dollar to expand
 * 
 * @param word char * word to check
 * @return true if the word contains a dollar to expand
 * @return false if the word does not contain a dollar to expand
 */
bool	is_expand_dollar(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
		{
			if (!is_expand_dollar_single_quote(word, &i))
				return (false);
		}
		if (word[i] == '"')
		{
			if (!is_expand_dollar_double_quote(word, &i))
				return (false);
		}
		if (word[i] == '$')
			return (true);
		++i;
	}
	return (false);
}
