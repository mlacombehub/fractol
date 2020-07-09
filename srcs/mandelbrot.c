/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:13:01 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/09 18:38:22 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		fol_init_mandelbrot(t_fol_t *fol)
{
	fol->f_type = 1;
	fol->fractal.color = 265;
	fol->fractal.i_max = 40;
	fol->fractal.zoom = 200;
	fol->fractal.set.p1 = (t_vec2_t){-2.4, -1.5};
}

static void		fol_putpixel(t_fol_t *fol, t_point_t point, int color)
{
	uint32_t	i;

	if ((point.x >= 0 && point.x < WIN_X) || (point.y >= 0 && point.y < WIN_Y))
	{
		color = mlx_get_color_value(fol->mlx.mlx, color);
		i = point.x + point.y * WIN_X;
		fol->mlx.data_addr[i] = color;
	}
}

void	fol_mandelbrot_calc(t_fol_t	*fol, t_set_t set)
{
	double tmp;

	for(fol->fractal.offset.x = 0 ; fol->fractal.offset.x < WIN_X ; fol->fractal.offset.x++)
	{
		for(fol->fractal.offset.y = 0 ; fol->fractal.offset.y < WIN_Y ; fol->fractal.offset.y++)
		{
			set.z.r = 0;
			set.z.i = 0;
			set.c.r = fol->fractal.offset.x / fol->fractal.zoom + set.p1.x;
			set.c.i = fol->fractal.offset.y / fol->fractal.zoom + set.p1.y;
			fol->fractal.i = 0;
			while (sqrt(set.z.r * set.z.r + set.z.i * set.z.i) < 4 && fol->fractal.i < fol->fractal.i_max)
			{
				tmp = set.z.r;
				set.z.r = set.z.r * set.z.r - set.z.i * set.z.i + set.c.r;
				set.z.i = 2 * tmp * set.z.i + set.c.i;
				fol->fractal.i++;
			}
			if (fol->fractal.i == fol->fractal.i_max)
				fol_putpixel(fol, fol->fractal.offset, 0);
			else
			{
				fol->fractal.i -= log(log(sqrt(set.z.r * set.z.r + set.z.i * set.z.i)))/log(2);
				fol->fractal.i = ((NB_COLOR - 1) * fol->fractal.i) / fol->fractal.i_max;
				fol_putpixel(fol, fol->fractal.offset, fol->fractal.color * fol->fractal.i);
			}
		}
	}
}

void	*fol_mandelbrot(void* tab)
{
	t_fol_t		*fol;
	// int			tmp;

	fol = (t_fol_t *)tab;
	fol_mandelbrot_calc(fol, fol->fractal.set);
	// fol->fractal.offset.x = 0;
	// tmp = fol->fractal.offset.y;
	// while (fol->fractal.offset.x < WIN_X)
	// {
	// 	fol->fractal.offset.y = tmp;
	// 	while (fol->fractal.offset.y < fol->fractal.y_max)
	// 	{
	// 		fol->fractal.offset.y++;
	// 	}
	// 	fol->fractal.offset.x++;
	// }
	return (tab);
}

void	fol_mandelbrot_thread(t_fol_t *fol)
{
	t_fol_t		tab[I_THREAD];
	pthread_t	t[I_THREAD];
	int			i;

	i = 0;
	while (i < I_THREAD)
	{
		ft_memcpy((void*)&tab[i], (void*)fol, sizeof(t_fol_t));
		tab[i].fractal.offset.y = W_THREAD * i;
		tab[i].fractal.y_max = W_THREAD * (i + 1);
		pthread_create(&t[i], NULL, fol_mandelbrot, &tab[i]);
		i++;
	}
	while (i--)
		pthread_join(t[i], NULL);
}
