/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:05:50 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/01 15:25:53 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_compound	*parse_line(char *line, char **envp, int exit_status)
{
	char		**lexed_line;
	t_compound	*coumpound_command;

	lexed_line = split_minishell(line);
	if (!lexed_line)
		error_failed_malloc();
	// debug_double_char(lexed_line, "Minishplit", 1);
	if (check_error(lexed_line))
		return (ft_free_dstr(lexed_line), NULL);
	coumpound_command = parsing(lexed_line);
	ft_free_dstr(lexed_line);
	if (!coumpound_command)
		exit(EXIT_FAILURE);
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
void	prompt(char **env)
{
	char				*buffer;
	t_compound			*compound_command;
	int					exit_status;

	signal(SIGINT, &sig_handler_prompt);
	signal(SIGQUIT, SIG_IGN);
	buffer = NULL;
	exit_status = 0;
	rl_attempted_completion_function = history_completion;
	while (1)
	{
		if (buffer)
			free(buffer);
		buffer = readline("minishell-0.1$ ");
		if (!buffer)
			break ;
		if (buffer && *buffer)
			add_history(buffer);
		compound_command = parse_line(buffer, env, exit_status);
		if (compound_command)
			exit_status = execute(compound_command, env);
	}
	ft_free_dstr(env);
	free(buffer);
}
