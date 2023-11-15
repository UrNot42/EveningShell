/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:00:09 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/15 19:08:31 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the redir type (between REDIR_OUT, REDIR_IN, HERE_DOC, APPEND)
 * 
 * @param str string to be checked
 * @return int the right type of redir, 0 otherwise
 */
int	get_redir_type(char const *str)
{
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	if (!ft_strcmp(str, "<<"))
		return (HERE_DOC);
	if (!ft_strcmp(str, ">"))
		return (REDIR_OUT);
	if (!ft_strcmp(str, "<"))
		return (REDIR_IN);
	return (0);
}
