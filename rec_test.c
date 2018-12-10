/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 10:23:46 by tduval            #+#    #+#             */
/*   Updated: 2018/12/10 14:54:52 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include "ft_ls.h"

void    rec_test(char *od, DIR *direc)
{
    t_stat      buf;
    t_dirent    *test;
    int         i;

    test = 0;
    i = 0;
    while (i < 3)
    {
        test = readdir(direc);
        i++;
    }
    if (test == 0)
    {
        ft_putendl(ft_strjoin(ft_strsub(od, 0, ft_strlen(od) - 1), ":") : od);
        return ;
    }
    if (stat(ft_strjoin(od, test->d_name), &buf) == -1)
        return ;
    if (S_ISDIR(buf.st_mode))
        rec_test(1, ft_strjoin(ft_strjoin(od, test->d_name), "/"), opendir(ft_strjoin(od, test->d_name)));
    ft_putendl(strcmp(od, "/") ? ft_strjoin(ft_strsub(od, 0, ft_strlen(od) - 1), ":") : od);
    if ()
    while (test)
    {
        ft_putendl(test->d_name);
        test = readdir(direc);

    }
    ft_putchar('\n');
}

int     main(int ac, char **av)
{
    t_dirent    **list;
    t_dirent    *dir;
    DIR         *didi;

    didi = opendir(av[1]);
    rec_test(ft_strjoin(av[1], "/"),  didi);
    return (0);
}