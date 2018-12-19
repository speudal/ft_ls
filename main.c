/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:51:55 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 07:22:36 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

static void	ordre(char **av)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = 0;
	while (av[i] && av[i + 1])
	{
		if (ft_strcmp(av[i], av[i + 1]) > 0)
		{
			tmp = av[i];
			av[i] = av[i + 1];
			av[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

void		free_all(t_inf *files, t_inf *dirs)
{
	t_inf	*tmp;

	while (files)
	{
		tmp = files;
		files = files->next;
		ft_strdel(&(tmp->path));
		free(tmp);
	}
	files = 0;
	while (dirs)
	{
		tmp = dirs;
		dirs = dirs->next;
		ft_strdel(&(tmp->path));
		free(tmp);
	}
	dirs = 0;
}

int			main(int ac, char **av)
{
	t_inf	*tmp;
	t_inf	*files;
	t_inf	*dirs;
	char	opts;
	int		i;

	i = 1;
	if ((opts = get_opts(ac, av)) == -1)
		return (0);
	while (ac > 1 && av[i] && av[i][0] == '-' && av[i][1] && (tmp = 0) == 0)
		i++;
	ordre(av + i);
	files = get_files(av + i, opts);
	if (!(dirs = get_dirs(av + i, opts)) && !files && !av[i])
		dirs = dir_new(".", opts);
	if (files)
	{
		hub_files(files, opts, 1);
		if (dirs)
			ft_putchar('\n');
	}
	if (dirs)
		hub_dirs(opts, dirs, (dirs && dirs->next) || (files));
	free_all(files, dirs);
	return (0);
}
