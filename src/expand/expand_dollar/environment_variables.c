/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:35:32 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 21:28:28 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_special_character(int c)
{
	if (c == ' ' || c == '\t' || c == '\'' || c == '"'
		|| c == '$' || c == '{' || c == '}' || c == '~' || c == '`'
		|| c == '&' || c == '?' || c == ';' || c == '(' || c == ')'
		|| c == '[' || c == ']' || c == '*' || c == '+' || c == '-'
		|| c == '@' || c == ':' || c == '.' || c == ',' || c == '/')
		return (1);
	return (0);
}

int	get_var_name_length(char const *str, int index)
{
	int	length;

	length = 0;
	++index;
	if (!ft_isalpha(str[index]) && str[index] != '_'
		&& ft_isdigit(str[index]))
	{
		return (1);
	}
	else if (!ft_isalpha(str[index]) && str[index] != '_'
		&& str[index] != '?' && !ft_isdigit(str[index]))
	{
		return (0);
	}
	else if (str[index] == '?')
	{
		return (1);
	}
	while (str[index] && !is_special_character(str[index]))
	{
		++index;
		++length;
	}
	return (length);
}

int	retrieve_var_name(char **var, char *str,
	int index_dollar, int size)
{
	int	i;

	i = 0;
	*var = ft_calloc(size + 1, sizeof(char));
	if (!*var)
		return (0);
	++index_dollar;
	while (i < size)
	{
		(*var)[i] = str[index_dollar];
		++index_dollar;
		++i;
	}
	return (1);
}
