/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:28:17 by aoberon           #+#    #+#             */
/*   Updated: 2023/11/01 18:28:25 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "minishell.h"

// ========================== HERE_DOCS ==========================

// -------------------------- HERE_DOC --------------------------

int		heredoc(t_exec *exec, char *keyword);

void	exit_heredoc(bool boolean, char **keyword, int *fd_write);

// -------------------------- OPEN_HEREDOC_FILE --------------------------

int		open_heredoc_write(char *filename);
int		open_heredoc_read(char **filename, char *filename_std);

#endif
