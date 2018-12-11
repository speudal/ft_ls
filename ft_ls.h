/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:52:20 by tduval            #+#    #+#             */
/*   Updated: 2018/12/11 22:01:02 by tduval           ###   ########.fr       */
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

typedef struct		s_inf
{
	char			*path;
	char			*name;
	t_stat			buf;
	struct s_inf	*next;
}					t_inf;

int					widthn(int n);
char				*get_opts(int ac, char **av);
char				**get_files(int ac, char **av);
char				**get_dirs(int ac, char **av);
void				sort_r(char **lst);
void				sort_alpha(char **lst);
void				sort_t(char **lst);
void				print_l(t_inf *fil, int pads[5]);
void				print_files(char **files, char *opts);

#endif
