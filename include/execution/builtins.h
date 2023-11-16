/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:51 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/16 15:32:19 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "exec_struct.h"

enum	e_bt_commands
{
	NOT_A_BT,
	BT_CD,
	BT_ECHO,
	BT_ENV,
	BT_EXIT,
	BT_EXPORT,
	BT_PWD,
	BT_UNSET,
};

// ========================== BUILTINS ==========================

// -------------------------- BUILTINS --------------------------

int	is_builtin(char *cmd);

// -------------------------- CD --------------------------

int	builtins_cd(char **args, char **env);

// -------------------------- ECHO --------------------------

int	builtins_echo(char **args);

// -------------------------- ENV --------------------------

int	env(char **env);

// -------------------------- EXIT --------------------------

int	check_exit_args(char **args);
int	builtins_exit(t_exec *ex, int i, int last_err, int fd_stdout);

// -------------------------- EXPORT --------------------------

int	ft_export(char ***env, char **args);

// -------------------------- PWD --------------------------

int	builtins_pwd(void);

// -------------------------- UNSET --------------------------

int	unset(char **env, char **args);

#endif
