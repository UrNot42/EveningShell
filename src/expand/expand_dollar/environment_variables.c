/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:35:32 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/15 19:03:02 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the char is a special character : 
 *(space, tab, ', ", $, {, }, ~, `, &, ?, ;, (, ), [, ], *, +, -, @, :, ., ,, /)
 * 
 * @param c char to check
 * @return true if the char is a special character
 * @return false if the char is not a special character
 */
static bool	is_special_character(char c)
{
	if (c == ' ' || c == '\t' || c == '\'' || c == '"'
		|| c == '$' || c == '{' || c == '}' || c == '~' || c == '`'
		|| c == '&' || c == '?' || c == ';' || c == '(' || c == ')'
		|| c == '[' || c == ']' || c == '*' || c == '+' || c == '-'
		|| c == '@' || c == ':' || c == '.' || c == ',' || c == '/')
		return (true);
	return (false);
}

/**
 * @brief Get the length of the environment variable name
 * 
 * @param str str containing the env var
 * @param index int of the first char of the env var in str
 * @return int the length of the env var name
 */
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

/**
 * @brief Retrieve the name of the environment variable from str
 * 
 * @param var var to be filled with the name of the env var
 * @param str str containing the env var to retrieve
 * @param index_dollar index of the first char of the env var in str
 * @param size size of the var name
 * @return int 1 if the var name was retrieved, 0 if malloc failed
 */
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
