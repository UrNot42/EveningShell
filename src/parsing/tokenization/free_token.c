/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:20:39 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/30 11:50:43 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *command_list)
{
	size_t	i;

	i = 0;
	if (!command_list)
		return ;
	while (command_list[i].type == -1)
	{
		if (command_list[i].content)
		{
			ft_free_dstr(command_list[i].content);
			command_list[i].content = NULL;
		}
		i++;
	}
	free(command_list);
}
