/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 19:16:22 by mlacombe          #+#    #+#             */
/*   Updated: 2019/05/31 16:47:39 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_puterror(int bool, char *msg)
{
	if (bool)
	{
		ft_putendl_fd(msg, 2);
		exit(TRUE);
	}
	return (0);
}
