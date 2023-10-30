/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:41:36 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/30 14:28:48 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

// ========================== EXPAND ==========================

// -------------------------- CHECK_FOR_DOLLAR --------------------------

size_t	check_for_dollar(char const *str, size_t *index_dollar);

// -------------------------- EXPAND_ONE_TOKEN --------------------------

int		expand_one_token(t_token token, char **env);

// -------------------------- EXPAND --------------------------

void	expand(t_token **token, char **env);

// -------------------------- QUOTES_MANAGEMENT --------------------------

char	*remove_quotes(char *word);

#endif
