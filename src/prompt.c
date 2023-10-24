/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:05:50 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/24 18:59:17 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*parse_line(char *line, char **envp)
{
	char	**parsed_lines;
	t_token	*token;

	parsed_lines = split_minishell(line);
	if (!parsed_lines)
		return (NULL);
	debug_double_char(parsed_lines, "Minishplit", 1);
	if (check_error(parsed_lines))
		return (ft_free_dstr(parsed_lines), NULL);
	token = tokenization(parsed_lines);
	if (!token)
		return (ft_free_dstr(parsed_lines), NULL);
	debug_token(token, "Tokenization");
	expansion(&token, envp);
	debug_token(token, "Expand");
	return (token);
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
	while (!error)
	{
		if (buffer)
			free(buffer);
		buffer = readline("minishell-0.1$ ");
		if (buffer[0] == 'q')
			error = true;
		add_history(buffer);
		tokens = parse_line(buffer, envp);
		// if (tokens)
			// execute(tokens, envp);
	}
	free(buffer);
}
