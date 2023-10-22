/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:20:39 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/16 11:17:17 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *command_list)
{
	size_t	i;

	i = 0;
	while (command_list && command_list[i])
	{
		if (command_list[i]->content)
			ft_free_dstr(command_list[i]->content);
		i++;
	}
	free(command_list);
}
