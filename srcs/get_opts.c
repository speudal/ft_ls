/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:36:27 by tduval            #+#    #+#             */
/*   Updated: 2018/12/18 00:38:59 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "libft.h"

static char	split(char *av, char opts)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (!ft_strchr("1Ralrt", av[i]))
		{
			ft_printf("ft_ls: illegal option -- %c\n", av[i]);
			ft_putendl("usage: ft_ls [-1Ralrt] [file ...]");
			return (-1);
		}
		opts = (av[i] == 'l' ? opts | OPT_L : opts);
		opts = (av[i] == 't' ? opts | OPT_T : opts);
		opts = (av[i] == 'a' ? opts | OPT_A : opts);
		opts = (av[i] == 'r' ? opts | OPT_SR : opts);
		opts = (av[i] == 'R' ? opts | OPT_BR : opts);
		i++;
	}
	return (opts);
}

char		get_opts(int ac, char **av)
{
	char	opts;
	int		i;

	i = 1;
	opts = 0;
	while (i < ac && av[i][0] == '-' && av[i][1])
	{
		if ((opts = (opts | split(av[i], opts))) == -1)
			return (-1);
		i++;
	}
	return (opts);
}
