/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_dstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:52:37 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/04 17:59:35 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Frees a Double string (char **) safely
void	ft_free_dstr(char **dstr)
{
	int	i;

	i = 0;
	while (dstr && dstr[i])
	{
		free(dstr[i]);
		i++;
	}
	free(dstr);
}
