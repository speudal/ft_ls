/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:51:55 by tduval            #+#    #+#             */
/*   Updated: 2018/12/11 21:43:16 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

int			main(int ac, char **av)
{
	char	**all[2];
	char	*opts;
	int		i;

	i = 0;
	if (!(opts = get_opts(ac, av)))
		return (0);
	sort_alpha(av + 1);
	if (!(all[0] = get_files(ac, av)))
		return (0);
	if (!(all[1] = get_dirs(ac, av)))
		return (0);
	print_files(all[0], opts);
	//print_dirs(all[1], opts);
	return (0);
}