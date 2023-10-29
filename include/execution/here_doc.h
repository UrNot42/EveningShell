/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:28:17 by aoberon           #+#    #+#             */
/*   Updated: 2023/10/27 19:06:05 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "minishell.h"

// ========================== HERE_DOCS ==========================

// -------------------------- HERE_DOC --------------------------

int		heredoc(char *keyword);

// -------------------------- KEYWORD_MANAGEMENT --------------------------

char	*get_keyword(char *keyword);

// -------------------------- OPEN_HEREDOC_FILE --------------------------

int		open_heredoc(int *fd_read, int *fd_write, char *filename);

#endif
