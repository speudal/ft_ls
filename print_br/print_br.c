/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:31:03 by tduval            #+#    #+#             */
/*   Updated: 2018/12/16 05:04:01 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

static t_inf	*get_fifi(DIR *gl, t_inf *dir, char *opts)
{
	t_dirent	*e;
	t_inf		*fils;
	t_inf		*cfils;

	cfils = 0;
	fils = 0;
	while ((e = readdir(gl)))
	{
		if (!cfils)
		{
			fils = any_new(ft_strjoin(ft_strjoin(dir->path, "/"), e->d_name), opts);
			cfils = fils;
		}
		else
		{
			fils->next = any_new(ft_strjoin(ft_strjoin(dir->path, "/"), e->d_name), opts);
			if (fils->next)
				fils = fils->next;
		}
	}
	return (cfils);
}

static t_inf	*getcpy(t_inf *fi)
{
	t_inf	*beg;
	t_inf	*fils;
	int		i;
	int		j;

	i = 0;
	j = 0;
	beg = 0;
	fils = 0;
	while (fi)
	{
		if (!fils)
		{
			fils = (t_inf *)malloc(sizeof(t_inf));
			fils->buf = fi->buf;
			fils->path = ft_strdup(fi->path);
			fils->next = 0;
			beg = fils;
		}
		else
		{
			fils->next = (t_inf *)malloc(sizeof(t_inf));
			fils->next->buf = fi->buf;
			fils->next->path = ft_strdup(fi->path);
			fils->next->next = 0;
			if (fils->next)
				fils = fils->next;
		}
		fi = fi ->next;
	}
	return (beg);
}

void	print_br(t_inf *dir, char *opts, int f)
{
	DIR			*gl;
	t_inf		*cfils;

	cfils = 0;
	if (!dir)
		return ;
	if (f)
		ft_printf("%s:\n", dir->path);
	if ((gl = opendir(dir->path)))
	{
		cfils = get_fifi(gl, dir, opts);
		if (ft_ami(opts, 'r'))
		{
			hub_files(getcpy(cfils), opts, 1, 1);
			if (ft_ami(opts, 't'))
				cfils = sort_time(cfils);
			cfils = sort_reverse(cfils);
		}
		else
			hub_files(cfils, opts, 1, 1);
		while (cfils)
		{
			if (S_ISDIR(cfils->buf.st_mode) &&
					(rev_chr(cfils->path)[0] != '.' || ft_ami(opts, 'a'))
					&& ft_strcmp(rev_chr(cfils->path), ".")
					&& ft_strcmp(rev_chr(cfils->path),  ".."))
				print_br(cfils, opts, 1);
			cfils = cfils->next;
		}
		closedir(gl);
	}
	else
		ft_printf("ft_ls: %s: Permission denied\n\n", rev_chr(dir->path));
}
