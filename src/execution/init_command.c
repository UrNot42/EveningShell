/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:27:54 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/29 13:28:07 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_cmds(t_token *token, t_cmd *cmd, t_file *file)
{
	int	c_index;

	c_index = 0;
	while (token->content)
	{
		if (token->type == CMD)
		{
			cmd[c_index].cmd = token->content[0];
			cmd[c_index].args = &token->content[1];
			cmd[c_index].in = NULL;
			cmd[c_index].out = NULL;
		}
		if (token->type == REDIR_IN || token->type == HERE_DOC)
			cmd[c_index].in = file++;
		if (token->type == REDIR_OUT || token->type == APPEND)
			cmd[c_index].out = file++;
		if (token->type == PIPE)
		{
			ft_free_dstr(token->content);
			token->content = NULL;
			c_index++;
		}
		token++;
	}
	return (0);
}