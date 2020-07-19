/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:13:01 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/19 18:45:33 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fol_mandelbrot_init(t_fol_t *fol)
{
	fol->f_type = 1;
	fol->fractal.color = 0x00A0A0A0;
	fol->fractal.i_max = 40;
	fol->fractal.zoom = 300;
	fol->fractal.set.p1 = (t_vec2_t){-2.5, -1.7};
}

void	*fol_mandelbrot(void *tab)
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
			fol_calc(fol, fol->fractal.set);
			fol->fractal.offset.y++;
		}
		fol->fractal.offset.x++;
	}
	return (tab);
}
