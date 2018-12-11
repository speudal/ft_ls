/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:52:20 by tduval            #+#    #+#             */
/*   Updated: 2018/12/11 19:24:28 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <dirent.h>
# include "libft.h"

typedef struct stat	t_stat;

char			*get_opts(int ac, char **av);
char			**get_files(int ac, char **av);
char			**get_dirs(int ac, char **av);
void			sort_r(char **lst);
void			sort_alpha(char **lst);
void			sort_t(char **lst);

#endif
