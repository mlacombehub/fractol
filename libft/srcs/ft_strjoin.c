/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:26:03 by mlacombe          #+#    #+#             */
/*   Updated: 2019/06/07 10:43:11 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *s;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	if (!(s = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	s = ft_strcpy(s, (char *)s1);
	s = ft_strcat(s, (char *)s2);
	if (s == NULL)
		return (NULL);
	return (s);
}
