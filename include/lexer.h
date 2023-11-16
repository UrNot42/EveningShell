/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:40:00 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 09:45:45 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// ========================== MINISHPLIT ==========================

// -------------------------- CHECK_ERROR --------------------------

int		check_error(char **argv);

// -------------------------- CHECK_QUOTATION_ERROR --------------------------

int		check_quotation_error(char **argv);

// -------------------------- CHECK_SYNTAX_ERROR --------------------------

int		check_syntax_error(char **argv);

// -------------------------- DOUBLE_QUOTES --------------------------

size_t	wl_double_quotes(char const *s);
size_t	get_next_double_quote(char const *s, size_t i);

// -------------------------- SINGLE_QUOTES --------------------------

size_t	wl_single_quotes(char const *s);
size_t	get_next_single_quote(char const *s, size_t i);	

// -------------------------- MINISHPLIT --------------------------

char	**minishplit(char const *s);
char	**ft_rewind_free(char **argv, size_t y);

// -------------------------- DOLLARS --------------------------

size_t	wl_dollars(char const *s);

// -------------------------- METACHARACTERS --------------------------

bool	is_metacharacter(char c);

size_t	wl_metacharacters(char const *s);

#endif
