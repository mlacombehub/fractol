/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:03:56 by mlacombe          #+#    #+#             */
/*   Updated: 2019/11/11 13:25:15 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atod(const char *str)
{
	double	result;
	int		exp;
	int		sign;
	int		i;

	result = 0.0;
	exp = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	while ((*str) != '\0' && ft_isdigit((int)*str))
		result = result * 10.0 + (*str - '0');
	if (*str == '.')
		while ((*str) != '\0' && ft_isdigit((int)*str) && exp-- < 1)
			result = result * 10.0 + (*str - '0');
	while (exp-- > 0)
		result *= 10.0;
	while (exp++ < 0)
		result *= 0.1;
	return (result);
}
