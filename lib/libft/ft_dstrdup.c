/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:06:57 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/31 17:06:27 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dstrdup(const char **dstr)
{
	int		nb_word;
	char	**new_dstr;

	nb_word = 0;
	if (!dstr)
		return (NULL);
	while (dstr[nb_word])
		nb_word++;
	new_dstr = ft_calloc(nb_word + 1, sizeof(char *));
	if (!new_dstr)
		return (NULL);
	nb_word = 0;
	while (dstr[nb_word])
	{
		new_dstr[nb_word] = ft_strdup(dstr[nb_word]);
		if (!new_dstr[nb_word])
			return (ft_free_dstr(new_dstr), NULL);
		nb_word++;
	}
	return (new_dstr);
}
