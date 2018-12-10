/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 12:29:29 by tduval            #+#    #+#             */
/*   Updated: 2018/12/10 19:45:45 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include "ft_ls.h"

int			check_opts(char *options)
{
	int	i;

	i = 0;
	while (options[i])
	{
		if (!(ft_strchr("lRart", options[i])))
		{
			ft_printf("ft_ls: illegal option -- %c\nusage: ft_ls [-ratlR] [file...]\n", options[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

t_params	get_args(int ac, char **av)
{
	t_params	ret;
	int			i;
	int			j;

	ret.opts = 0;
	ret.paths = 0;
	ret.err = 0;
	i = 1;
	j = 0;
	if (av[1][0] == '-' && av[1][1])
	{	
		if (!(ret.opts = ft_strdup(av[i] + 1)) || !(check_opts(ret.opts)))
		{
			ret.err = 1;
			return (ret);
		}
		i++;
	}
	if (!(ret.paths = (char **)malloc(sizeof(char *) * (ac - i + 1))))
	{
		ret.err = 1;
		return (ret);
	}
	while (i < ac)
	{
		if (!(ret.paths[j] = ft_strdup(av[i])))
		{
			ret.err = 1;
			return (ret);
		}
		i++;
		j++;
	}
	ret.paths[j] = 0;
	return (ret);
}

int			main(int ac, char **av)
{
	int			i;
	int			j;
	t_stat		buf;
	char		**lstdir;
	char		**lstfls;
	t_params	p;

	j = 0;
	if (ac < 2)
		ft_ls_nomod();
	else
	{	
		i = 0;
		p = get_args(ac, av);
		if (p.err)
			return (0);
		while (p.paths[i])
		{
			if (stat(p.paths[i], &buf) == -1)
				ft_printf("ft_ls: %s: No such file or directory\n", p.paths[i]);
			i++;
		}
		if (!(lstdir = fill_lstdirs(p.paths)))
			return (0);
		if (!(lstfls = fill_lstfls(p.paths)))
			return (0);
		print_names(lstfls, p.opts);
	}
	return (0);
}
