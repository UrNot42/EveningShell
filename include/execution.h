/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:51 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/05 12:08:19 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// -------------------------- BUILTINS --------------------------

void	builtins(int argc, char **argv);

// -------------------------- BUILTINS_CD --------------------------

int		detect_cd(char **argv);
int		builtins_cd(char **argv);

// -------------------------- BUILTINS_ECHO --------------------------

int		detect_echo(char **argv);

void	builtins_echo(char **argv);

// -------------------------- BUILTINS_EXIT --------------------------

int		detect_exit(char **argv);

void	builtins_exit(void);

// -------------------------- BUILTINS_PWD --------------------------

int		detect_pwd(char **argv);
int		buitlins_pwd(char **argv);

#endif
