/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:26:18 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/11 16:24:40 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check for redirection syntax error
 * 
 * @param argv argv array of strings to check
 * @param n index of the redirection
 * @return int returns 1 if there is an error, 0 otherwise
 */
int	check_syntax_redir(char **argv, size_t n)
{
	if (!argv[n + 1] || get_redir_type(argv[n + 1]) || argv[n + 1][0] == '|')
	{
		printf("minishell$: syntax error near unexpected token `%s'\n",
			argv[n + 1]);
		return (1);
	}
	return (0);
}

/**
 * @brief Check for pipe syntax error
 * 
 * @param argv array of strings to check
 * @param n index of the pipe
 * @return int returns 1 if there is an error, 0 otherwise
 */
int	check_syntax_pipe(char **argv, size_t n)
{
	if (n == 0)
	{
		printf("minishell$: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (!argv[n + 1] || get_redir_type(argv[n + 1]))
	{
		printf("minishell$: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (argv[n + 1][0] == '|')
	{
		printf("minishell$: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Check if there is a syntax error in the command line
 * 
 * @param argv array of strings to check
 * @return int returns 1 if there is an error, 0 otherwise
 */
int	check_syntax_error(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '|')
		{
			if (check_syntax_pipe(argv, i))
				return (1);
		}
		i++;
	}
	i = 0;
	while (argv[i])
	{
		if (get_redir_flag(argv[i]) != -1)
		{
			if (check_syntax_redir(argv, i))
				return (1);
		}
		i++;
	}
	return (0);
}
