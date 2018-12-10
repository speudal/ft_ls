/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 12:33:01 by tduval            #+#    #+#             */
/*   Updated: 2018/12/10 19:47:43 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <unistd.h>
# include "libft.h"

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_params
{
	char	err;
	char	*opts;
	char	**paths;
}						t_params;

typedef struct			s_files
{
	t_dirent		*dir;
	t_stat			*stat;
	struct s_files	*next;
}						t_files;

void					ft_ls_nomod(void);
void					full_ls(t_params p, DIR **dirs);
char					**fill_lstdirs(char **paths);
char					**fill_lstfls(char **paths);
void					print_names(char **lstfls, char *options);

#endif
