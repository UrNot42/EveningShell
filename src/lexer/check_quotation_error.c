/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotation_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:59:17 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 09:38:43 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the single quotes are closed
 * 
 * @param str string to check
 * @param i starting index
 * @return int 1 if the single quotes are not closed, 0 otherwise
 */
static int	check_end_single_quotes(char const *str, size_t *i)
{
	*i += 1;
	while (str[*i])
	{
		if (str[*i] == '\'')
			return (0);
		*i += 1;
	}
	printf("minishell$: syntax error: single quotes not closed\n");
	return (1);
}

/**
 * @brief Check if the double quotes are closed
 * 
 * @param str string to check
 * @param i starting index
 * @return int 1 if the double quotes are not closed, 0 otherwise
 */
static int	check_end_double_quotes(char const *str, size_t *i)
{
	*i += 1;
	while (str[*i])
	{
		if (str[*i] == '"')
			return (0);
		*i += 1;
	}
	printf("minishell$: syntax error: double quotes not closed\n");
	return (1);
}

/**
 * @brief Check quotation errors on one string
 * 
 * @param str string to check
 * @return int 1 if there is an error, 0 otherwise
 */
static int	check_one_string_quotes(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			if (check_end_single_quotes(str, &i))
				return (1);
		if (str[i] == '"')
			if (check_end_double_quotes(str, &i))
				return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Check for quotation error in the command line
 * 
 * @param argv array of strings to check
 * @return int 1 if there is an error, 0 otherwise
 */
int	check_quotation_error(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		if (check_one_string_quotes(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
