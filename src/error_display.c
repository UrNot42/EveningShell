/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:16:47 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/02 18:22:34 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Display error message when malloc fails and exit
 * 
 */
void	error_failed_malloc(void)
{
	printf("minishell: malloc failed\n");
	exit(1);
}
