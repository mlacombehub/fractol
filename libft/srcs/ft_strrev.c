/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 13:28:46 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/18 18:09:16 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = str;
	j = ft_strlen(str);
	while (--j > 0)
	{
		ret[i] = str[j];
		i++;
	}
	return (ret);
}
