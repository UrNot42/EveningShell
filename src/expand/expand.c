/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:53:58 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/03 15:57:59 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Expands one by one each content's compound, compound by compound
 * Expand means to replace the environment variables (starting with $) by their
 * content (contained in the char ** env) And remove the quotes
 *
 * @param compound compound containing the content to expand
 * @param env char ** of the environment variables
 * @param exit_status int containing the exit status of the last command
 */
void	expand(t_compound **compound, char **env, int exit_status)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((*compound)[i].type != UNSET && (*compound)[i].type != -1)
	{
		if ((*compound)[i].type != HERE_DOC)
		{
			if (expand_one_compound((*compound)[i], env, exit_status) == -1)
			{
				(free_compound(*compound), error_failed_malloc());
			}
		}
		j = 0;
		while ((*compound)[i].content[j])
		{
			(*compound)[i].content[j]
				= remove_quotes((*compound)[i].content[j]);
			if (!(*compound)[i].content[j++])
			{
				(free_compound(*compound), error_failed_malloc());
			}
		}
		i++;
	}
}
