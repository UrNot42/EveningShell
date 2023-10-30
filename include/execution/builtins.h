/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:51 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/30 10:17:52 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// -------------------------- BUILTINS --------------------------

void	builtins(int argc, char **argv);
bool	is_builtin(char *cmd);

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

int		unset(char **env, char **args);
int		ft_export(char **env, char **args);
void	env(char **env);

#endif
