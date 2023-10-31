/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:53:58 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/30 21:20:12 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Expands one by one each content's token, token by token
 * Expand means to replace the environment variables (starting with $) by their
 * content (contained in the char ** env) And remove the quotes
 * 
 * @param token token containing the content to expand
 * @param env char ** of the environment variables
 */
void	expand(t_token **token, char **env)
{
	size_t	i;
	size_t	j;

	i = -1;
	while ((*token)[++i].type != -1)
	{
		if ((*token)[i].type != HERE_DOC)
		{
			if (expand_one_token((*token)[i], env) == -1)
			{
				free_token(*token);
				error_failed_malloc();
			}
		}
		j = 0;
		while ((*token)[i].content[j])
		{
			(*token)[i].content[j] = remove_quotes((*token)[i].content[j]);
			if (!(*token)[i].content[j++])
			{
				free_token(*token);
				error_failed_malloc();
			}
		}
	}
}