/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:57:08 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/31 12:55:33 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*snew;

	snew = malloc((ft_strlen((char *) s) + 1) * (sizeof(char)));
	if (!snew)
		return (NULL);
	ft_strlcpy(snew, s, ft_strlen((char *) s) + 1);
	return (snew);
}
