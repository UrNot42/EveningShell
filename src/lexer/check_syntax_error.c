/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:26:18 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/20 18:29:16 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the redirection is ambiguous redirection
 * 
 * @param arg char * to check
 * @param env char ** of the environment variables
 * @return int 1 if there is an error, -42 if a malloc failed, 0 otherwise
 */
int	check_syntax_redir_ambiguous(char *arg, char **env)
{
	int		index_env;
	int		index_word;
	char	*var_name;

	if (arg[0] == '$')
	{
		index_word = 0;
		index_env = find_index_env(arg, &index_word, env);
		if (index_env == -1)
		{
			if (arg[index_word + 1] == '\0')
			{
				retrieve_var_name(&var_name, arg, 0,
					get_var_name_length(arg, 0));
				if (!var_name)
					return (-42);
				write(2, "MarmiShell: $", 13);
				write(2, var_name, ft_strlen(var_name));
				write(2, ": ambiguous redirect\n", 21);
				free(var_name);
				return (1);
			}
		}
	}
	return (0);
}

/**
 * @brief Check for redirection syntax error
 * 
 * @param argv array of strings to check
 * @param n index of the redirection
 * @param env char ** of the environment variabless
 * @return int 1 if there is an error, 0 otherwise
 */
int	check_syntax_redir(char **argv, size_t n, char **env)
{
	int		redir_ambiguous;

	if (!argv[n + 1] || get_redir_type(argv[n + 1]) || argv[n + 1][0] == '|')
	{
		write(2, "MarmiShell: syntax error near unexpected token `", 48);
		write(2, argv[n + 1], ft_strlen(argv[n + 1]));
		write(2, "'\n", 2);
		return (1);
	}
	redir_ambiguous = check_syntax_redir_ambiguous(argv[n + 1], env);
	if (redir_ambiguous != 0)
		return (redir_ambiguous);
	return (0);
}

/**
 * @brief Check for pipe syntax error
 *
 * @param argv array of strings to check
 * @param n index of the pipe
 * @return int 1 if there is an error, 0 otherwise
 */
int	check_syntax_pipe(char **argv, size_t n)
{
	if (n == 0)
	{
		write(2, "MarmiShell: syntax error near unexpected token `|'\n", 51);
		return (1);
	}
	if (!argv[n + 1] || argv[n + 1][0] == '|')
	{
		write(2, "MarmiShell: syntax error near unexpected token `|'\n", 51);
		return (1);
	}
	return (0);
}

/**
 * @brief Check for all redirection syntax error in each argument
 * 
 * @param argv char ** array of strings to check
 * @param env char ** of the environment variables
 * @return int 1 if there is an error, -42 if a malloc failed, 0 otherwise
 */
int	check_syntax_error_redir(char **argv, char **env)
{
	int	i;
	int	redir_error;

	i = 0;
	while (argv[i])
	{
		if (get_redir_type(argv[i]))
		{
			redir_error = check_syntax_redir(argv, i, env);
			if (redir_error == -42)
				return (-42);
			if (redir_error)
				return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Check if there is a syntax error in the command line
 *
 * @param argv array of strings to check
 * @return int 1 if there is an error, -42 if a malloc failed, 0 otherwise
 */
int	check_syntax_error(char **argv, char **env)
{
	int	i;
	int	redir_error;

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
	redir_error = check_syntax_error_redir(argv, env);
	if (redir_error == -42)
		return (-42);
	if (redir_error == 1)
		return (1);
	return (0);
}
