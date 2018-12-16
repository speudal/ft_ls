/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:51:55 by tduval            #+#    #+#             */
/*   Updated: 2018/12/16 03:43:17 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

static void	ordre(char **av)
{
	char	*tmp;
	int		i;

	i = 0;
	while (av[i] && av[i + 1])
	{
		if (ft_strcmp(av[i], av[i + 1]) > 0)
		{
			tmp = av[i];
			av[i] = av[i + 1];
			av[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

void		free_all(char *opts, t_inf *files, t_inf *dirs)
{
	t_inf	*tmp;

	if (opts)
		free(opts);
	while (files)
	{
		tmp = files;
		files = files->next;
		free(tmp->path);
		free(tmp);
	}
	while (dirs)
	{
		tmp = dirs;
		dirs = dirs->next;
		free(tmp->path);
		free(tmp);
	}
}

int			main(int ac, char **av)
{
	t_inf	*files;
	t_inf	*dirs;
	char	*opts;
	int		i;
	int		j;

	j = 0;
	i = 1;
	dirs = 0;
	files = 0;
	if (!(opts = get_opts(ac, av)))
		return (0);
	while (ac > 1 && av[i] && av[i][0] == '-' && av[i][1])
		i++;
	ordre(av + i);
	files = get_files(av + i, opts);
	if (!(dirs = get_dirs(av + i, opts)) && !files && !av[i])
		dirs = dir_new(".", opts);
	if (files)
		hub_files(files, opts, dirs && ac > i + 1 && dirs ? 1 : 0, 0);
	hub_dirs(opts, dirs, (dirs && dirs->next) || (files));
	free_all(opts, files, dirs);
	return (0);
}
