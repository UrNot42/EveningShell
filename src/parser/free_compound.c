/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_compound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:20:39 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/14 19:59:23 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
