/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:51 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/04 18:56:52 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// -------------------------- BUILTINS_CD --------------------------

int	detect_cd(char **argv);

// -------------------------- BUILTINS_ECHO --------------------------

int	detect_echo(int argc, char **argv);

// -------------------------- BUILTINS_EXIT --------------------------

int	detect_exit(char **argv);

// -------------------------- BUILTINS_PWD --------------------------

int	detect_pwd(char **argv);

#endif
