/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:07:20 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/04 10:00:01 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>

// -------------------------- BUILTINS_CD --------------------------

int	detect_cd(char **argv);

// -------------------------- BUILTINS_ECHO --------------------------

int	detect_echo(int argc, char **argv);

// -------------------------- BUILTINS_PWD --------------------------

int	detect_pwd(char **argv);

// -------------------------- UTILS --------------------------

int	ft_strlen(char *str);
int	ft_strcmp(const char *s1, const char *s2);

#endif
