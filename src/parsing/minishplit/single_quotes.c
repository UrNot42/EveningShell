/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:56:27 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/31 12:47:00 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the next char that is a single quote
 * 
 * @param s string to go through
 * @param i index to start from
 * @return size_t index of the next single quote
 */
size_t	get_next_single_quote(char const *s, size_t i)
{
	i++;
	while (s[i] != '\'' && s[i])
	{
		i++;
	}
	return (i);
}

/**
 * @brief count the length of a word depending of the single quotes' rules
 * 
 * @param s string to count in
 * @return size_t size of the word
 */
size_t	wl_single_quotes(char const *s)
{
	size_t	i;

	i = get_next_single_quote(s, 0);
	while (s[i] && !is_metacharacter(s[i + 1]))
	{
		i++;
		if (s[i] == '\'')
			i = get_next_single_quote(s, i);
		if (s[i] == '"')
			i = get_next_double_quote(s, i);
	}
	if (s[i])
		i++;
	return (i);
}
