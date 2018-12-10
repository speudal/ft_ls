/* ************************************************************************** */
/**/
/*:::  ::::::::   */
/*   ft_ls_nomod.c  :+:  :+::+:   */
/*+:+ +:+ +:+ */
/*   By: tduval <tduval@student.42.fr>  +#+  +:+   +#+*/
/*+#+#+#+#+#+   +#+   */
/*   Created: 2018/12/10 13:33:30 by tduval#+##+# */
/*   Updated: 2018/12/10 13:39:27 by tduval   ###   ########.fr   */
/**/
/* ************************************************************************** */

#include <dirent.h>
#include "ft_ls.h"

void	ft_ls_nomod(void)
{
	int			i;
	t_dirent	*ui;
	t_stat		buf;
	DIR			*dir;

	i = 0;
	dir = opendir(".");
	ui = readdir(dir);
	while (i < 2)
	{
		ui = readdir(dir);
		i++;
	}
	while (ui)
	{
		if (ui->d_name[0] != '.')
			ft_putendl(ui->d_name);
		ui = readdir(dir);
	}
}