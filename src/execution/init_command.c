/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:27:54 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/01 14:42:04 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_cmds(t_compound *token, t_cmd *cmd, t_file *file)
{
	int	c_index;

	c_index = 0;
	while (token->content)
	{
		if (token->type == CMD)
			cmd[c_index] = (t_cmd){token->content[0],
				&token->content[0], NULL, NULL};
		if (token->type == REDIR_IN || token->type == HERE_DOC)
			cmd[c_index].in = file++;
		if (token->type == REDIR_OUT || token->type == APPEND)
			cmd[c_index].out = file++;
		if (token->type == PIPE)
		{
			token->content = NULL;
			c_index++;
		}
		token++;
	}
	return (0);
}
