/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:05:50 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/12 21:49:52 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Take a line (char *) and convert it to a array of compound.
 *
 * @param line char * line to be parsed
 * @param envp array of strings containing the environment variables
 * @param exit_status int exit status of the last command
 * @return t_compound* array of compounds created from the line
 */
t_compound	*parse_line(char *line, char **envp, int exit_status)
{
	char		**tokens;
	t_compound	*coumpound_command;

	tokens = minishplit(line);
	if (!tokens)
		error_failed_malloc();
	// debug_double_char(tokens, "Minishplit", 1);
	if (check_error(tokens))
		return (ft_free_dstr(tokens), NULL);
	coumpound_command = parsing(tokens);
	ft_free_dstr(tokens);
	if (!coumpound_command)
		error_failed_malloc();
	// debug_compound(coumpound_command, "Parsing");
	expand(&coumpound_command, envp, exit_status);
	// debug_compound(coumpound_command, "Expand");
	return (coumpound_command);
}

// TEST FUNCTION FOR COMPLETETION IMPLEMENTATION
char	**history_completion(const char *text, int start, int end)
{
	char		**match;
	int			i[2];
	char		*str;
	HIST_ENTRY	*hist_entry;
	char		*entry;

	match = NULL;
	i[0] = start;
	i[1] = 0;
	while (i[0] < end)
	{
		hist_entry = history_get(i[0]++);
		if (hist_entry)
		{
			entry = hist_entry->line;
			if (ft_strncmp(entry, text, ft_strlen(text)) == 0)
			{
				str = ft_strdup(entry);
				match = ft_realloc(match, (i[1] + 2) * sizeof(char *), 0);
				match[i[1]++] = str;
				match[i[1]] = NULL;
			}
		}
	}
	return (match);
}

/**
 * @brief prompt of the shell.
 *        WIP as it uses the highly unstable funtion readline
 *        unstable in the sense of memory so most testing of funtions
 *        ought to be done without using the prompt
 *
 *        although it is the main loop of Minishell
 *2
 */
void	prompt(char ***env)
{
	char				*buffer;
	t_compound			*compound_command;
	int					exit_status;

	set_signal(SIGQUIT, SIG_IGN);
	set_signal(SIGINT, sig_handler_prompt);
	buffer = NULL;
	exit_status = 0;
	rl_attempted_completion_function = history_completion;
	while (1)
	{
		g_signal = 0;
		if (buffer)
			free(buffer);
		buffer = readline("minishell-0.1$ ");
		if (g_signal != 0)
			exit_status = g_signal;
		if (!buffer)
			(ft_free_dstr(*env), write(2, "exit\n", 5), exit(exit_status));
		if (buffer && *buffer)
			add_history(buffer);
		compound_command = parse_line(buffer, *env, exit_status);
		if (compound_command)
			exit_status = execute(compound_command, env, exit_status);
	}
}
