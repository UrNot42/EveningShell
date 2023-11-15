/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_compound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:20:39 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/15 19:08:59 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Free a array of compounds and its content
 * 
 * @param command_list t_compound * array of compounds to be freed
 */
void	free_compound(t_compound *command_list)
{
	size_t	i;

	i = 0;
	if (!command_list)
		return ;
	while (command_list[i].type != UNSET)
	{
		if (command_list[i].content)
		{
			ft_free_dstr(command_list[i].content);
			command_list[i].content = NULL;
		}
		i++;
	}
	free(command_list);
	command_list = NULL;
}
