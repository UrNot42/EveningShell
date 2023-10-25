/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:53:58 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/25 13:12:09 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Expands one by one each content's token, token by token
 * Expand means to replace the environment variables (starting with $) by their
 * content (contained in the char ** env)
 * 
 * @param token token containing the content to expand
 * @param env char ** of the environment variables
 */
void	expansion(t_token **token, char **env)
{
	size_t	i;

	(void)env;
	i = 0;
	while ((*token)[i].type != -1)
	{
		if ((*token)[i].type != HERE_DOC)
		{
			if (expand_one_token((*token)[i], env) == -1)
			{
				printf("FREE AND EXIT\n");
				return ;
			}
		}
		i++;
	}
}
