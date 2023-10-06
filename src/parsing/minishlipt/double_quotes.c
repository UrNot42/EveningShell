/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:42:32 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/06 13:33:09 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the char that is a double quote
 * 
 * @param s string to go through
 * @param i index to start from
 * @return size_t index of the next double quote
 */
static size_t	get_next_double_quote(char const *s, size_t i)
{
	i++;
	while (s[i] != '"' && s[i])
	{
		i++;
	}
	return (i);
}

/**
 * @brief count the length of a word depending of the double quotes' rules
 * 
 * @param s string to count in
 * @return size_t size of the word
 */
size_t	wl_double_quotes(char const *s)
{
	size_t	i;

	i = 0;
	i = get_next_double_quote(s, i);
	while (!is_metacharacter(s[i + 1]) && s[i])
	{
		i++;
		if (s[i] == '"')
		i = get_next_double_quote(s, i);
	}
	i++;
	return (i);
}
