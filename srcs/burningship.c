/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:05:27 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/19 18:29:39 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fol_burningship_init(t_fol_t *fol)
{
	fol->f_type = 3;
	fol->fractal.color = 0x00A0A0A0;
	fol->fractal.i_max = 40;
	fol->fractal.zoom = 280;
	fol->fractal.set.p1 = (t_vec2_t){-2.2, -2.1};
}

void	fol_burningship_calc(t_fol_t *fol, t_set_t set)
{
	t_cmplx_t	pow_z;
	double		tmp;

	fol->fractal.i = 0;
	pow_z = (t_cmplx_t){set.z.r * set.z.r, set.z.i * set.z.i};
	while (sqrt(pow_z.r + pow_z.i) < 4 && fol->fractal.i < fol->fractal.i_max)
	{
		tmp = set.z.r;
		set.z.r = pow_z.r - pow_z.i + set.c.r;
		set.z.i = fabs(2 * tmp * set.z.i) + set.c.i;
		pow_z = (t_cmplx_t){set.z.r * set.z.r, set.z.i * set.z.i};
		fol->fractal.i++;
	}
	if (fol->fractal.i == fol->fractal.i_max)
		fol_putpixel(fol, fol->fractal.offset, 0);
	else
	{
		fol->fractal.i -= log(log(sqrt(pow_z.r + pow_z.i))) / log(2);
		fol->fractal.i = ((NB_COLOR - 1) * fol->fractal.i)
						/ fol->fractal.i_max;
		fol_putpixel(fol, fol->fractal.offset,
						fol->fractal.color * fol->fractal.i);
	}
}

void	*fol_burningship(void *tab)
{
	t_fol_t		*fol;
	int			i;

	fol = (t_fol_t *)tab;
	fol->fractal.offset.x = 0;
	i = fol->fractal.offset.y / W_THREAD;
	while (fol->fractal.offset.x < WIN_X)
	{
		fol->fractal.offset.y = W_THREAD * i;
		while (fol->fractal.offset.y < fol->fractal.y_max)
		{
			fol->fractal.set.c.r = fol->fractal.offset.x / fol->fractal.zoom
									+ fol->fractal.set.p1.x;
			fol->fractal.set.c.i = fol->fractal.offset.y / fol->fractal.zoom
									+ fol->fractal.set.p1.y;
			fol->fractal.set.z.r = 0;
			fol->fractal.set.z.i = 0;
			fol_burningship_calc(fol, fol->fractal.set);
			fol->fractal.offset.y++;
		}
		fol->fractal.offset.x++;
	}
	return (tab);
}
