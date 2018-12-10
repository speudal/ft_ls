/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fls_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduval <tduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 12:45:03 by tduval            #+#    #+#             */
/*   Updated: 2018/12/10 12:48:28 by tduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

t_files     *fls_new(t_dirent *dir, t_dirent *stat)
{
    t_files *fls;

    if (!(fls = (t_files *)malloc(sizeof(t_files))))
        return (0);
    fls->dir = dir;
    fls->stat = stat;
    fls->next = 0;
    return (fls);
}