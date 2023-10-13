/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:41:36 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/13 17:57:16 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

// ========================== EXPANSION ==========================

// -------------------------- CHECK_FOR_DOLLAR --------------------------

size_t	check_for_dollar(char const *str, size_t *index_dollar);

// -------------------------- EXPAND_ONE_TOKEN --------------------------

int		expand_one_token(t_token token, char **env);

// -------------------------- EXPANSION --------------------------

void	expansion(t_token **token, char **env);

#endif
