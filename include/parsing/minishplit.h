/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishplit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:40:00 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/13 13:44:07 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHPLIT_H
# define MINISHPLIT_H

# include "minishell.h"

// ========================== MINISHPLIT ==========================

// -------------------------- CHECK_ERROR --------------------------

int		check_error(char **argv);

// -------------------------- CHECK_QUOTING_ERROR --------------------------

int		check_quoting_error(char **argv);

// -------------------------- CHECK_SYNTAX_ERROR --------------------------

int		check_syntax_error(char **argv);

// -------------------------- DOUBLE_QUOTES --------------------------

size_t	wl_double_quotes(char const *s);

// -------------------------- SINGLE_QUOTES --------------------------

size_t	wl_single_quotes(char const *s);

// -------------------------- MINISHPLIT --------------------------

char	**split_minishell(char const *s);

// -------------------------- DOLLARS --------------------------

size_t	wl_dollars(char const *s);

// -------------------------- METACHARACTERS --------------------------

bool	is_metacharacter(char c);

size_t	wl_metacharacters(char const *s);

#endif