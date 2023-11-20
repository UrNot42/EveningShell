/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:05:50 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/20 18:28:38 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the char is a space or a tab
 *
 * @param c char to check
 * @return int return 1 if the char is a space or a tab, 0 otherwise
 */
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

/**
 * @brief Check if the line is null (only spaces and tabs)
 *
 * @param line line to check
 * @return int return 1 if the line is null, 0 otherwise
 */
int	is_line_null(char *line)
{
	int	i;

	i = 0;
	while (line [i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

/**
 * @brief Take a line (char *) and convert it to a array of compound.
 *
 * @param line char * line to be parsed
 * @param envp array of strings containing the environment variables
 * @param exit_status int exit status of the last command
 * @return t_compound* array of compounds created from the line
 */
t_compound	*parse_line(char *line, char **envp, int *exit_status)
{
	int			checkerror;
	char		**tokens;
	t_compound	*coumpound_command;

	if (is_line_null(line))
		return (NULL);
	tokens = minishplit(line);
	if (!tokens)
		(ft_free_dstr(envp), error_malloc_failed(true));
	checkerror = check_error(tokens, envp);
	if (checkerror != 0)
	{
		if (checkerror == -42)
			(ft_free_dstr(tokens), ft_free_dstr(envp),
				error_malloc_failed(true));
		*exit_status = 2;
		return (ft_free_dstr(tokens), NULL);
	}
	coumpound_command = parsing(tokens);
	ft_free_dstr(tokens);
	if (!coumpound_command)
		(ft_free_dstr(envp), error_malloc_failed(true));
	expand(&coumpound_command, envp, *exit_status);
	return (coumpound_command);
}

/**
 * @brief prompt of the shell.
 *        WIP as it uses the highly unstable funtion readline
 *        unstable in the sense of memory so most testing of funtions
 *        ought to be done without using the prompt
 *
 *        although it is the main loop of Minishell
 *
 */
void	prompt(char ***env)
{
	char				*buffer;
	t_compound			*compound_command;
	int					exit_status;

	signal(SIGINT, &sig_handler_prompt);
	signal(SIGQUIT, SIG_IGN);
	buffer = NULL;
	exit_status = 0;
	while (1)
	{
		g_signal = 0;
		if (buffer)
			free(buffer);
		buffer = readline("MarmiShell-4.2$ ");
		if (g_signal != 0)
			exit_status = g_signal;
		if (!buffer)
			(ft_free_dstr(*env), write(2, "exit\n", 5), exit(exit_status));
		if (buffer && *buffer)
			add_history(buffer);
		compound_command = parse_line(buffer, *env, &exit_status);
		if (compound_command)
			exit_status = execute(compound_command, env, exit_status);
	}
}
