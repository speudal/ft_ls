/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 21:34:34 by tduval            #+#    #+#             */
/*   Updated: 2018/12/11 22:09:12 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_files(char **files, char *opts)
{
	t_inf	*tt;
	int		i;
	int		pads[5] = {0, 0, 0, 0, 0};

	i = 0;
	if (ft_strchr(opts, 't'))
		sort_t(files);
	if (ft_strchr(opts, 'r'))
		sort_r(files);
	if (!(tt = (t_inf *)malloc(sizeof(t_inf))))
		return ;
	if (ft_strchr(opts, 'l'))
	{
		while (files[i])
		{
			lstat(files[i], &(tt->buf));
			if (widthn(buf.st_nlink) > pad[0])
				pad[0] = widthn(tt->buf.st_nlink);
			if (ft_strlen(getpwuid(tt->buf.st_uid)) > pad[1])
				pad[1] = ft_strlen(get.pwuid(tt->buf.st_uid));
			if (ft_strlen(getgrgid(tt->buf.std_gid)) > pad[2])
				pad[2] = ft_strlen(getgrgid(tt->buf.std_gid));
			if (widthn(tt->buf.st_size) > pad[3])
				pad[3] = widthn(tt->buf.st_size);
		}
		i = 0;
		while (files[i])
		{
			{
				tt->path = ft_strdup(files[i]);
				tt->name = ft_strdup(files[i]);
				lstat(files[i], &(tt->buf));
				print_l(tt, 0, 0);
				ft_putchar('\n');
			}
		}
	}
	else
	{
		while (files[i])
			ft_putendl(files[i]);
		i++;
	}
}
