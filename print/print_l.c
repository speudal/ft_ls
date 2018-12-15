/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 19:41:00 by tduval            #+#    #+#             */
/*   Updated: 2018/12/15 02:43:54 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include <uuid/uuid.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "ft_ls.h"

static	char *rev_chr(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i && str[i] != '/')
		i--;
	return (str + i);
}

static void	f1(t_inf *fil)
{
	char	f1[11];

	f1[0] = '-';
	f1[0] = S_ISFIFO(fil->buf.st_mode) ? 'p' : f1[0];
	f1[0] = S_ISSOCK(fil->buf.st_mode) ? 's' : f1[0];
	f1[0] = S_ISLNK(fil->buf.st_mode) ? 'l' : f1[0];
	f1[0] = S_ISDIR(fil->buf.st_mode) ? 'd' : f1[0];
	f1[0] = S_ISCHR(fil->buf.st_mode) ? 'c' : f1[0];
	f1[0] = S_ISBLK(fil->buf.st_mode) ? 'b' : f1[0];
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
}

static char	*formatf(char *time)
{
	return (ft_strcat(ft_strsub(time, 4, 7), ft_strsub(time, 19, 5)));
}

static char	*formati(char *time)
{
	char	*tmp;
	tmp = time;
	time = ft_strsub(time, 4, 12);
	return (time);
}

void	print_l(t_inf *fil, int *pads)
{
	struct passwd	*p;
	struct group	*q;
	char			*npath;
	int				f;
	char			*tim;

	f = 0;
	p = getpwuid(fil->buf.st_uid);
	q = getgrgid(fil->buf.st_gid);
	npath = 0;
	if (time (0) - fil->buf.st_mtime > 1578000)
		tim = formatf(ctime(&(fil->buf.st_mtime)));
	else
		tim = formati(ctime(&(fil->buf.st_mtime)));
	f1(fil);
	ft_printf("  %*d %-*s  %-*s  %*d %s %s", pads[0],
				fil->buf.st_nlink, pads[1], p->pw_name,
				pads[2], q->gr_name, pads[3], fil->buf.st_size, tim,
				fil->path);
}
