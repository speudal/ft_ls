/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:52:20 by tduval            #+#    #+#             */
/*   Updated: 2018/12/15 03:01:25 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <dirent.h>
# include "libft.h"

typedef struct dirent	t_dirent;

typedef struct stat		t_stat;

typedef struct			s_inf
{
	char				*path;
	t_stat				buf;
	struct s_inf		*next;
}						t_inf;

int						widthn(int n);
char					*get_opts(int ac, char **av);
t_inf					*dir_new(char *path, char *opts);
t_inf					*fil_new(char *path, char *opts);
t_inf					*any_new(char *path, char *opts);
t_inf					*get_dirs(char **av, char *opts);
t_inf					*get_files(char **av, char *opts);
void					print_dirs(char *opts, t_inf *dirs, char flag);
t_inf					*sort_reverse(t_inf *lst);
t_inf					*sort_alpha(t_inf *lst);
t_inf					*sort_time(t_inf *lst);
int						ft_ami(char *str, char c);
void					print_l(t_inf *fil, int pads[5]);
void					print_files(t_inf *top, char *opts, char flag);
void					print_file(char *opts, t_dirent *f);
void					free_all(char *opts, t_inf *files, t_inf *dirs);
void					print_rec(t_inf *dir, char *opts, int f);

#endif
