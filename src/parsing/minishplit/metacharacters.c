/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:05:37 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/06 13:31:23 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief checks if a character is a metacharacter (space, tab, <, >, |)
 * 
 * @param c character to check
 * @return true if it is a metacharacter
 * @return false if it is not a metacharacter
 */
bool	is_metacharacter(char c)
{
	if (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

/**
 * @brief count the length of a word depending of the metacharacters' rules
 * 
 * @param s string to count in
 * @return size_t size of the word
 */
size_t	wl_metacharacters(char const *s)
{
	if (s[0] == '|' || s[0] == ' ' || s[0] == '\t')
		return (1);
	if (s[0] == '<')
	{
		if (s[1] == '<')
			return (2);
		return (1);
	}
	if (s[0] == '>')
	{
		if (s[1] == '>')
			return (2);
		return (1);
	}
	return (0);
}
