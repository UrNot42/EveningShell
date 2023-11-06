/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:27:54 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/06 19:39:52 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_cmd_files(t_compound *element, t_cmd *cmd, t_file *file)
{
	int	e_id;

	e_id = 0;
	printf("cmd: 1 %p\n", cmd);
	while (element[e_id].content)
	{
		printf("cmd: 2 %p\n", cmd);
		if (cmd != NULL
			&& (element[e_id].type == REDIR_IN
				|| element[e_id].type == HERE_DOC))
			cmd->in = file++;
		if (cmd != NULL
			&& (element[e_id].type == REDIR_OUT
				|| element[e_id].type == APPEND))
			cmd->out = file++;
		if (element[e_id].type == PIPE)
			cmd++;
		element++;
	}
	return (e_id);
}

int	fill_cmds(t_compound *element, t_cmd *cmd, t_file *file)
{
	int	c_index;
	int	e_id;

	c_index = 0;
	e_id = 0;
	while (element[e_id].content)
	{
		if (element[e_id].type == CMD)
			cmd[c_index] = (t_cmd){element[e_id].content[0],
				&element[e_id].content[0], NULL, NULL};
		if (element[e_id].type == PIPE)
			c_index++;
		e_id++;
	}
	fill_cmd_files(element, cmd, file);
	return (c_index);
}
