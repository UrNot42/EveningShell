/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:05:50 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/30 18:16:09 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Malloc Failed

t_token	*parse_line(char *line, char **envp)
{
	char	**lexed_line;
	t_token	*token;

	lexed_line = split_minishell(line);
	if (!lexed_line)
		exit(EXIT_FAILURE);
	// debug_double_char(lexed_line, "Minishplit", 1);
	if (check_error(lexed_line))
		return (ft_free_dstr(lexed_line), NULL);
	token = tokenization(lexed_line);
	ft_free_dstr(lexed_line);
	if (!token)
		exit(EXIT_FAILURE);
	// debug_token(token, "Tokenization");
	expand(&token, envp);
	// debug_token(token, "Expand");
	return (token);
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
 *
 */
void	prompt(char **envp)
{
	char	*buffer;
	bool	error;
	t_token	*tokens;

	buffer = NULL;
	error = false;
	rl_attempted_completion_function = history_completion;
	while (!error)
	{
		if (buffer)
			free(buffer);
		buffer = readline("minishell-0.1$ ");
		if (buffer[0] == 'q')
			error = true;
		if (buffer && *buffer)
			add_history(buffer);
		tokens = parse_line(buffer, envp);
		if (tokens)
			execute(tokens, envp);
	}
	free(buffer);
}
