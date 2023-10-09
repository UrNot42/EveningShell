/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:31 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/06 13:09:16 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// -------------------------- SPLIT_MINISHELL --------------------------

char	**split_minishell(char const *s);

// -------------------------- double_quote --------------------------

size_t	wl_double_quotes(char const *s);

// -------------------------- single_quote --------------------------

size_t	wl_single_quotes(char const *s);

// -------------------------- dollar --------------------------

size_t	wl_dollars(char const *s);

// -------------------------- METACHARACTERS --------------------------

bool	is_metacharacter(char c);

size_t	wl_metacharacters(char const *s);

#endif
