/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:35:53 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/03 18:50:53 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the char c is a special character
 * 
 * @param c char to check
 * @return int 1 if c is a special character, 0 otherwise
 */
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

/**
 * @brief Moving the index_dollar to the end of the single quotes string
 * 
 * @param str string to check in
 * @param index_dollar index to move
 * @return int return 1 if the end of the string is reached, 0 otherwise
 */
static int	dollar_in_single_quotes(char const *str, size_t *index_dollar)
{
	*index_dollar += 1;
	while (str[*index_dollar] && str[*index_dollar] != '\'')
		*index_dollar += 1;
	if (!str[*index_dollar])
		return (1);
	return (0);
}

/**
 * @brief Check for a dollar in double quotes string
 * 
 * @param str string to check in
 * @param index_dollar index of the first char of the dollar in the string str
 * @return size_t return the length of the environment variable name if there is
 * a dollar in the string str, 0 otherwise
 */
static size_t	dollar_in_double_quotes(char const *str, size_t *index_dollar)
{
	size_t	expand_length;

	expand_length = 0;
	*index_dollar += 1;
	while (str[*index_dollar] && str[*index_dollar] != '"')
	{
		if (str[*index_dollar] == '$')
		{
			*index_dollar += 1;
			while (str[*index_dollar]
				&& !is_special_character(str[*index_dollar])
				&& str[*index_dollar] != '|'
				&& str[*index_dollar] != '<' && str[*index_dollar] != '>')
			{
				*index_dollar += 1;
				expand_length++;
			}
			return (expand_length);
		}
		*index_dollar += 1;
	}
	return (0);
}

/**
 * @brief Check for a dollar in non quoted (single or double) string
 * 
 * @param str string to check in
 * @param index_dollar index of the first char of the dollar in the string str
 * @return size_t return the length of the environment variable name if there is
 * a dollar in the string str, 0 otherwise
 */
static size_t	dollar_alone(char const *str, size_t *index_dollar)
{
	size_t	expand_length;

	expand_length = 0;
	*index_dollar += 1;
	if (!ft_isalpha(str[*index_dollar]) && str[*index_dollar] != '_'
		&& ft_isdigit(str[*index_dollar]))
	{
		*index_dollar += 1;
		return (1);
	}
	else if (!ft_isalpha(str[*index_dollar]) && str[*index_dollar] != '_'
		&& str[*index_dollar] != '?' && !ft_isdigit(str[*index_dollar]))
	{
		return (0);
	}
	while (str[*index_dollar] && !is_special_character(str[*index_dollar]))
	{
		*index_dollar += 1;
		expand_length++;
	}
	return (expand_length);
}

/**
 * @brief Check if there is a dollar in the string str
 * 
 * @param str string to check
 * @param index_dollar index of the first char of the dollar in the string str
 * @return size_t return the length of the environment variable name if there is
 * a dollar in the string str, else return 0
 */
size_t	check_for_dollar(char const *str, size_t *index_dollar)
{
	size_t	expand_length;

	*index_dollar = 0;
	while (str[*index_dollar])
	{
		if (str[*index_dollar] == '\'')
		{
			if (dollar_in_single_quotes(str, index_dollar))
				return (0);
		}
		if (str[*index_dollar] == '"')
		{
			expand_length = dollar_in_double_quotes(str, index_dollar);
			if (expand_length)
				return (expand_length);
			if (!str[*index_dollar])
				return (0);
		}
		if (str[*index_dollar] == '$')
		{
			return (dollar_alone(str, index_dollar));
		}
		*index_dollar += 1;
	}
	return (0);
}
