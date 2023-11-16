/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_interactive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:45:10 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/16 19:21:14 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_last_nwline(char *buff)
{
	int	i;

	i = ft_strlen(buff);
	if (i <= 1)
		return ;
	i--;
	if (buff[i] == '\n')
		buff[i] = '\0';
}

void	prompt_non_interactive(char ***env)
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
		buffer = get_next_line(0);
		if (g_signal != 0)
			exit_status = g_signal;
		if (!buffer)
			(ft_free_dstr(*env), exit(exit_status));
		replace_last_nwline(buffer);
		compound_command = parse_line(buffer, *env, &exit_status);
		if (compound_command)
			exit_status = execute(compound_command, env, exit_status);
	}
}
