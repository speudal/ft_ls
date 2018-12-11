/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 19:41:00 by tduval            #+#    #+#             */
/*   Updated: 2018/12/11 22:09:11 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include <uuid/uuid.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "ft_ls.h"

static void	*f1(t_inf *fil)
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
	f1[3] = S_IXUSR & fil->buf.st_mode ? 'x' : '-';
	f1[4] = S_IRGRP & fil->buf.st_mode ? 'r' : '-';
	f1[5] = S_IWGRP & fil->buf.st_mode ? 'w' : '-';
	f1[6] = S_IXGRP & fil->buf.st_mode ? 'x' : '-';
	f1[7] = S_IROTH & fil->buf.st_mode ? 'r' : '-';
	f1[8] = S_IWOTH & fil->buf.st_mode ? 'w' : '-';
	f1[9] = S_IWOTH & fil->buf.st_mode ? 'x' : '-';
	ft_putstr(f1);
}

static char	*formati(char *time)
{
	char	*tmp;

	tmp = time;
	time = ft_strsub(time, 4, 12);
	return (time);
}

void	print_l(t_inf *fil, int pads[5])
{
	struct passwd	*p;
	struct group	*q;
	char			*tim;

	p = getpwuid(fil->buf.st_uid);
	q = getgrgid(fil->buf.st_gid);
	tim = formati(ctime(&(fil->buf.st_mtime)));
	f1(fil);
	ft_putstr("  ");
	ft_printf("%d", fil->buf.st_nlink);
	ft_putstr(" ");
	ft_printf("%s", p->pw_name);
	ft_putstr("  ");
	ft_printf("%s", q->gr_name);
	ft_putstr(" ");
	ft_putnbr(fil->buf.st_size);
	ft_putstr("  ");
	ft_putstr(tim);
	ft_putstr("  ");
	ft_putstr(fil->name);
}
