/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstr_is_sorted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:04:32 by ulevallo          #+#    #+#             */
/*   Updated: 2023/11/20 18:17:47 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief checks if an array of string is sorted
 *
 * @param dstr
 * @return true
 * @return false
 */
int	ft_dstr_is_sorted(char **dstr)
{
	int	i;

	i = 0;
	while (dstr[i] && dstr[i + 1])
	{
		if (ft_strcmp(dstr[i], dstr[i + 1]) > 0)
			return (0);
		i++;
	}
	return (1);
}
