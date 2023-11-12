/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expand_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 21:34:33 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 22:26:49 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_expand_dollar_single_quote(char *word, int *i)
{
	*i += 1;
	while (word[*i] && word[*i] != '\'')
		*i += 1;
	if (!word[*i])
		return (false);
	return (true);
}

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
