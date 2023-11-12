/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_no_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:40:15 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/12 15:41:04 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get a length of a number.
 * 
 * @param n number to get the length.
 * @return int return the length.
 */
int	ft_nbrlen(int n)
{
	if (n < 0)
		n = -n;
	if (n < 10)
		return (1);
	return (1 + ft_nbrlen(n / 10));
}

/**
 * @brief Converts an integer to a string without malloc.
 * 
 * @param n integer to convert.
 * @param result string to store the result.
 */
void	ft_itoa_no_malloc(int n, char result[12])
{
	unsigned int	tmp;
	size_t			size;

	if (n < 0)
		tmp = -n;
	else
		tmp = n;
	size = (ft_nbrlen(tmp) + (n < 0));
	ft_bzero(result, 10);
	result[size--] = '\0';
	if (n == 0)
		result[0] = '0';
	while (tmp > 0)
	{
		result[size] = (tmp % 10) + '0';
		tmp /= 10;
		size--;
	}
	if (n < 0)
		result[0] = '-';
}
