/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:02:01 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/06 13:31:39 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief count the length of a word depending of the dollars' rules
 * 
 * @param s string to count in
 * @return size_t size of the word
 */
size_t	wl_dollars(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] == '$')
		i++;
	while (!is_metacharacter(s[i]) && s[i] != '/' && s[i])
	{
		i++;
		if (s[i] == '$')
			return (i);
	}
	return (i);
}
