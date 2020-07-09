/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_close_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:50:17 by mlacombe          #+#    #+#             */
/*   Updated: 2020/02/27 12:18:04 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int	ft_open_close_fd(char *doc)
{
	t_point_t	fd;
	char		res_a[13];
	char		res_b[13];
	int			i;

	if ((fd.x = open(doc, O_RDONLY)) < 0)
	{
		ft_putendl_fd("Problem with opening file", 2);
		return (0);
	}
	res_a[0] = (char)read(fd.x, res_a, 13);
	close(fd.x);
	if ((fd.y = open(doc, O_RDONLY)) < 0)
		return (0);
	res_b[0] = (char)read(fd.y, res_b, 13);
	close(fd.y);
	i = 0;
	while (i < ft_min(res_a[0], res_b[0]))
		res_a[i] != res_b[i] ? i = 42 : i++;
	if (i == 42)
	{
		ft_putendl_fd("Problem with reading file", 2);
		return (0);
	}
	return (1);
}
