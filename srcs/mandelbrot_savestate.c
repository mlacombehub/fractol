/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_savestate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:13:01 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/09 17:24:03 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		fol_init_mandelbrot(t_fol_t *fol)
{
	fol->f_type = 1;
	fol->fractal.color = 265;
	fol->fractal.i_max = 50;
	fol->fractal.zoom = 300;
	fol->fractal.set.p1.x = -2.05;
	fol->fractal.set.p1.y = -1.3;
}

static void		fol_putpixel(t_fol_t *fol, t_point_t point, int color)
{
	if (fol->fractal.offset.x < WIN_X && fol->fractal.offset.y < WIN_Y)
	{
		color = mlx_get_color_value(fol->mlx.mlx, color);
		ft_memcpy(fol->mlx.data_addr + 4 * WIN_Y * point.y + 4 * point.x, &color, sizeof(int));
	}
}

void	fol_mandelbrot_calc(t_fol_t	*fol, t_set_t set)
{
	set.c.r = fol->fractal.offset.x / fol->fractal.zoom + set.p1.x;
	set.c.i = fol->fractal.offset.y / fol->fractal.zoom + set.p1.y;
	set.z.r = 0;
	set.z.i = 0;
	fol->fractal.i = 0;
	while (set.z.r * set.z.r + set.z.i * set.z.i < 4 && fol->fractal.i < fol->fractal.i_max)
	{
		set.tmp = set.z.r;
		set.z.r = set.z.r * set.z.r - set.z.i * set.z.i + set.c.r;
		set.z.i = 2 * set.z.i * set.tmp + set.c.i;
		fol->fractal.i++;
	}
	if (fol->fractal.i == fol->fractal.i_max)
		fol_putpixel(fol, fol->fractal.offset, 0);
	else
		fol_putpixel(fol, fol->fractal.offset, fol->fractal.color * fol->fractal.i);
}

void	*fol_mandelbrot(void* tab)
{
	t_fol_t		*fol;
	int			tmp;

	fol = (t_fol_t *)tab;
	fol->fractal.offset.x = 0;
	tmp = fol->fractal.offset.y;
	while (fol->fractal.offset.x < WIN_X)
	{
		fol->fractal.offset.y = tmp;
		while (fol->fractal.offset.y < fol->fractal.y_max)
		{
			fol_mandelbrot_calc(fol, fol->fractal.set);
			fol->fractal.offset.y++;
		}
		fol->fractal.offset.x++;
	}
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
	mlx_put_image_to_window(fol->mlx.mlx, fol->mlx.win, fol->mlx.img, 0, 0);
}
