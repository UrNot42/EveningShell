/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:05:50 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/29 19:54:32 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*parse_line(char *line, char **envp)
{
	char	**parsed_lines;
	t_token	*token;

	parsed_lines = split_minishell(line);
	if (!parsed_lines)
		return (NULL);
	// debug_double_char(parsed_lines, "Minishplit", 1);
	if (check_error(parsed_lines))
		return (ft_free_dstr(parsed_lines), NULL);
	token = tokenization(parsed_lines);
	if (!token)
		return (ft_free_dstr(parsed_lines), NULL);
	// debug_token(token, "Tokenization");
	expansion(&token, envp);
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
	int		fd_heredoc;

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
		if (!tokens)
			break ;
		if (tokens[0].type == HERE_DOC)
		{
			fd_heredoc = heredoc(tokens[0].content[1]);
			// debug_heredoc(fd_heredoc);
			close(fd_heredoc);
		}
		if (tokens)
			execute(tokens, envp);
	}
	free(buffer);
}
