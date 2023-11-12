/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:53:58 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 21:34:48 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_one_compound(t_compound *compound,
	char **env, int exit_status)
{
	int	j;

	j = 0;
	while (compound->content[j])
	{
		if (compound->type != HERE_DOC
			&& is_expand_dollar(compound->content[j]))
		{
			if (!expand_one_content(&compound, &j, env, exit_status))
				return (-1);
		}
		else
		{
			compound->content[j]
				= remove_quotes(compound->content[j]);
			if (!compound->content[j])
			{
				return (-1);
			}
		}
		++j;
	}
	return (1);
}

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
	int	i;

	i = 0;
	while ((*compound)[i].type != UNSET && (*compound)[i].type != -1)
	{
		if (expand_one_compound(&(*compound)[i], env, exit_status) == -1)
			(free_compound(*compound), error_failed_malloc());
		++i;
	}
}

// echo $HOME"$USER"'$PATH'"'$?'"$TOTO'"$PATH"'
// /mnt/nfs/homes/aoberonaoberon$PATH'0'"$PATH"

// echo "toto$HOME"'$USER toto'"'toto'"
