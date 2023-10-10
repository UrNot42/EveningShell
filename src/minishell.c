/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:06:16 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/09 18:22:51 by ulevallo         ###   ########.fr       */
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
void	prompt(void)
{
	char	*buffer;
	bool	error;

	buffer = NULL;
	error = false;
	while (!error)
	{
		if (buffer)
			free(buffer);
		buffer = readline("minishell$:");
		if (buffer[0] == 'q')
			error = true;
		add_history(buffer);
		builtins(0, split_minishell(buffer));
	}
}

/**
 * @brief Main that is bound to change as it is mainly used to redirect
 * to change funtions
 *
 */
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	prompt();
	return (0);
}
