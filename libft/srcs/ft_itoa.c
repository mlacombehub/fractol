/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:28:30 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/16 09:59:07 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n = -n;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*dst;
	size_t	i;
	size_t	count;
	long	tmp_n;

	tmp_n = (long)n;
	i = 0;
	count = ft_nlen(n);
	if (tmp_n < 0 || count == 0)
		count++;
	if (!(dst = ft_strnew(count)))
		return (FALSE);
	if (tmp_n < 0)
	{
		tmp_n = -tmp_n;
		dst[0] = '-';
		i++;
	}
	while (count-- > i)
	{
		dst[count] = (tmp_n % 10) + '0';
		tmp_n /= 10;
	}
	return (dst);
}

char		*ft_itoa_base(int value, int base)
{
	static char	rep[16];
	static char	buf[66];
	char		*ptr;
	int			num;

	ft_memcpy(rep, "0123456789ABCDEF", 16);
	ptr = &buf[65];
	*ptr = '\0';
	num = value;
	if (base < 2 || base > 16)
		return (NULL);
	(value < 0) ? value *= -1 : 42;
	(value == 0) ? (*--ptr = rep[value % base]) : 42;
	while (value != 0)
	{
		*--ptr = rep[value % base];
		value /= base;
	}
	(num < 0 && base == 10) ? (*--ptr = '-') : 42;
	return (ptr);
}
