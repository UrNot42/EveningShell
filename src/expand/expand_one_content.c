/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_one_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:23:20 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 21:20:30 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_one_content(t_compound **compound, int *index, char **env,
	int exit_status)
{
	char	**new_content;

	new_content = create_new_content(
			(t_expand_dollar){(*compound)->content[*index], env, exit_status});
	if (!new_content)
		return (-1);
	(*compound)->content = insert_char2d_into_char2d((*compound)->content,
			new_content, index);
	return (1);
}
