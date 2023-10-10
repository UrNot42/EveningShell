/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:26:18 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/10 17:39:36 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_error(t_token *token)
{
	size_t	i;

	i = 0;
	while (token[i].content)
	{
		if (token[i].type == REDIR_IN)
		{
			if (!token[i + 1].content || token[i + 1].type != CMD)
			{
				printf("minishell$: syntax error missing file for\
					redirection in\n");
				return (1);
			}
		}
		if (token[i].type == REDIR_OUT)
		{
			if (!token[i + 1].content || token[i + 1].type != CMD)
			{
				printf("minishell$: syntax error missing file for\
					redirection out\n");
				return (1);
			}
		}
		if (token[i].type == HERE_DOC)
		{
			if (!token[i + 1].content || token[i + 1].type != CMD)
			{
				printf("minishell$: syntax error missing file for\
					heredoc\n");
				return (1);
			}
		}
		if (token[i].type == APPEND)
		{
			if (!token[i + 1].content || token[i + 1].type != CMD)
			{
				printf("minishell$: syntax error missing file for\
					append\n");
			}
		}
		if (token[i].type == PIPE)
		{
			if (!token[i + 1].content || token[i + 1].type != CMD)
			{
				printf("minishell$: syntax error missing file for pipe\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
