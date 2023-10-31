/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:20:31 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/31 15:59:03 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishplit.h"
# include "tokenization.h"
# include "expand.h"

// ========================== PROMPT ==========================

void	prompt(char **envp);
t_token	*parse_line(char *line, char **envp, int exit_status);

#endif
