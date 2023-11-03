/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:27:54 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/03 12:56:06 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_cmds(t_compound *element, t_cmd *cmd, t_file *file)
{
	int	c_index;

	c_index = 0;
	while (element->content)
	{
		if (element->type == CMD)
			cmd[c_index] = (t_cmd){element->content[0],
				&element->content[0], NULL, NULL};
		if (element->type == REDIR_IN || element->type == HERE_DOC)
			cmd[c_index].in = file++;
		if (element->type == REDIR_OUT || element->type == APPEND)
			cmd[c_index].out = file++;
		if (element->type == PIPE)
			c_index++;
		element++;
	}
	return (0);
}
