/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 21:05:50 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/13 21:30:16 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		tokens = parse_line(buffer);
		expansion(&tokens, envp);
		if (tokens)
			execute(tokens, envp);
	}
	free(buffer);
}

t_token	*parse_line(char *line)
{
	char	**parsed_lines;
	t_token	*token;

	parsed_lines = split_minishell(line);
	if (!parsed_lines)
		return (NULL);
	if (check_error(parsed_lines))
		return (ft_free_dstr(parsed_lines), NULL);
	token = tokenization(parsed_lines);
	if (!token)
		return (ft_free_dstr(parsed_lines), NULL);
	return (token);
}
