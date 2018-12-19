/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_br.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 03:06:38 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 06:43:00 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

static t_inf	*splifi(t_inf *dir, t_inf **fils, char opts, t_dirent *e)
{
	char	*tmp;
	char	*tmp2;

	tmp = 0;
	tmp2 = 0;
	tmp = ft_strapp(dir->path, '/');
	tmp2 = ft_strjoin(tmp, e->d_name);
	*fils = any_new(tmp2, opts);
	ft_strdel(&(tmp));
	ft_strdel(&(tmp2));
	return (*fils);
}

static t_inf	*get_fifi(DIR *gl, t_inf *dir, char opts)
{
	t_dirent	*e;
	char		*tmp;
	char		*tmp2;
	t_inf		*fils;
	t_inf		*cfils;

	cfils = 0;
	fils = 0;
	while ((e = readdir(gl)))
	{
		if (!cfils)
			cfils = splifi(dir, &fils, opts, e);
		else
		{
			tmp = ft_strapp(dir->path, '/');
			tmp2 = ft_strjoin(tmp, e->d_name);
			fils->next = any_new(tmp2, opts);
			ft_strdel(&(tmp));
			ft_strdel(&(tmp2));
			if (fils->next)
				fils = fils->next;
		}
	}
	return (cfils);
}

static void		free_lst(t_inf *fi)
{
	t_inf	*tmp;

	while (fi)
	{
		tmp = fi;
		fi = fi->next;
		ft_strdel(&(tmp->path));
		ft_memdel((void **)&tmp);
	}
}

static void		splitit(t_inf **cfils, char opts)
{
	t_inf		*tmp;

	tmp = *cfils;
	if (S_ISDIR((*cfils)->buf.st_mode) &&
			(rev_chr((*cfils)->path)[0] != '.' || opts & OPT_A)
				&& ft_strcmp(rev_chr((*cfils)->path), ".")
					&& ft_strcmp(rev_chr((*cfils)->path), ".."))
		print_br((*cfils), opts, 1);
	*cfils = (*cfils)->next;
}

void			print_br(t_inf *dir, char opts, int f)
{
	DIR			*gl;
	t_inf		*cfils;
	t_inf		*fils;

	cfils = 0;
	fils = 0;
	if (!dir)
		return ;
	if (f)
		ft_printf("\n%s:\n", dir->path[0] == '/' ? dir->path + 1 : dir->path);
	if ((gl = opendir(dir->path)))
	{
		cfils = get_fifi(gl, dir, opts);
		fils = cfils;
		hub_files(cfils, opts, 0);
		while (cfils)
			splitit(&cfils, opts);
		free_lst(fils);
		closedir(gl);
	}
	else
		ft_printf("ft_ls: %s: Permission denied\n", rev_chr(dir->path));
}
