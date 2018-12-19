/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 19:41:00 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 05:56:16 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/xattr.h>
#include <uuid/uuid.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "ft_ls.h"

static char	f_1_0(t_inf *fil)
{
	char	c;

	c = '-';
	c = S_ISFIFO(fil->buf.st_mode) ? 'p' : c;
	c = S_ISSOCK(fil->buf.st_mode) ? 's' : c;
	c = S_ISLNK(fil->buf.st_mode) ? 'l' : c;
	c = S_ISDIR(fil->buf.st_mode) ? 'd' : c;
	c = S_ISCHR(fil->buf.st_mode) ? 'c' : c;
	c = S_ISBLK(fil->buf.st_mode) ? 'b' : c;
	return (c);
}

static void	f1(t_inf *fil)
{
	char	*f1;

	if (!(f1 = ft_strnew(11)))
		return ;
	f1[0] = f_1_0(fil);
	f1[1] = S_IRUSR & fil->buf.st_mode ? 'r' : '-';
	f1[2] = S_IWUSR & fil->buf.st_mode ? 'w' : '-';
	if (S_IXUSR & fil->buf.st_mode)
		f1[3] = S_ISUID & fil->buf.st_mode ? 's' : 'x';
	else
		f1[3] = S_ISUID & fil->buf.st_mode ? 'S' : '-';
	f1[4] = S_IRGRP & fil->buf.st_mode ? 'r' : '-';
	f1[5] = S_IWGRP & fil->buf.st_mode ? 'w' : '-';
	if (S_IXGRP & fil->buf.st_mode)
		f1[6] = S_ISGID & fil->buf.st_mode ? 's' : 'x';
	else
		f1[6] = S_ISGID & fil->buf.st_mode ? 'S' : '-';
	f1[7] = S_IROTH & fil->buf.st_mode ? 'r' : '-';
	f1[8] = S_IWOTH & fil->buf.st_mode ? 'w' : '-';
	if (S_IXOTH & fil->buf.st_mode)
		f1[9] = S_ISVTX & fil->buf.st_mode ? 't' : 'x';
	else
		f1[9] = S_ISVTX & fil->buf.st_mode ? 'T' : '-';
	ft_putstr(f1);
	free(f1);
}

static char	*formati(char *tim, t_inf *fil)
{
	char	*tmp;
	char	*tmp2;

	tmp = 0;
	tmp2 = 0;
	if (time(0) - fil->buf.st_mtime > 15778800)
	{
		if (!(tmp = ft_strsub(tim, 4, 7)))
			return (0);
		if (!(tmp2 = ft_strsub(tim, 19, 5)))
		{
			free(tmp);
			return (0);
		}
		tim = ft_strcat(tmp, tmp2);
		ft_strdel(&(tmp2));
	}
	else
		tim = ft_strsub(tim, 4, 12);
	return (tim);
}

static void	les_print(t_inf *fil, int *pads, char *tim, char *iitt[2])
{
	struct passwd	*p;
	struct group	*q;

	p = getpwuid(fil->buf.st_uid);
	q = getgrgid(fil->buf.st_gid);
	if (!(S_ISBLK(fil->buf.st_mode) || S_ISCHR(fil->buf.st_mode)))
		ft_printf("  %*d %-*s  %-*s  %*d %s %s\n", pads[0],
			fil->buf.st_nlink, pads[1], p ? p->pw_name : iitt[0],
			pads[2], q ? q->gr_name : iitt[1], pads[3], fil->buf.st_size, tim,
			S_ISLNK(fil->buf.st_mode) ? fil->path : rev_chr(fil->path));
	else
		ft_printf("  %*d %-*s  %-*s  %*d, %*d %s %s\n", pads[0],
			fil->buf.st_nlink, pads[1], p ? p->pw_name : iitt[0],
			pads[2], q ? q->gr_name : iitt[1], pads[3], major(fil->buf.st_rdev),
			pads[5], minor(fil->buf.st_rdev), tim,
			S_ISLNK(fil->buf.st_mode) ? fil->path : rev_chr(fil->path));
}

void		print_l(t_inf *fil, int *pads)
{
	int				f;
	char			*tim;
	char			*iitt[2];

	tim = 0;
	f = 0;
	iitt[0] = ft_itoa(fil->buf.st_uid);
	iitt[1] = ft_itoa(fil->buf.st_gid);
	if (!(tim = formati(ctime(&(fil->buf.st_mtime)), fil)))
		return ;
	f1(fil);
	les_print(fil, pads, tim, iitt);
	ft_strdel(&(tim));
	ft_strdel(&(iitt[0]));
	ft_strdel(&(iitt[1]));
}
