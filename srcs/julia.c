/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 18:51:28 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/15 19:19:46 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fol_julia_init(t_fol_t *fol)
{
	fol->f_type = 2;
	fol->fractal.color = 0x00FFFFFF;
	fol->fractal.i_max = 40;
	fol->fractal.zoom = 300;
	fol->fractal.set.p1 = (t_vec2_t){-1.7, -1.5};
	fol->fractal.set.new_c = (t_cmplx_t){M_PI, M_PI};
}

void	*fol_julia(void *tab)
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
			fol->fractal.set.c.r = 0.785 * cos(fol->fractal.set.new_c.r);
			fol->fractal.set.c.i = 0.785 * sin(fol->fractal.set.new_c.i);
			fol->fractal.set.z.r = fol->fractal.offset.x / fol->fractal.zoom
									+ fol->fractal.set.p1.x;
			fol->fractal.set.z.i = fol->fractal.offset.y / fol->fractal.zoom
									+ fol->fractal.set.p1.y;
			fol_calc(fol, fol->fractal.set);
			fol->fractal.offset.y++;
		}
		fol->fractal.offset.x++;
	}
	return (tab);
}
