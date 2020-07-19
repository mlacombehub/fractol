/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:36:32 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/19 18:07:56 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		close_screen(void *param)
{
	(void)param;
	exit(1);
	return (0);
}

int		hook(int key, t_fol_t *fol)
{
	if (fol->tom_hook == 1)
	{
		key == KEY_Z ? fol->fractal.color -= 0x00000001 : 42;
		key == KEY_X ? fol->fractal.color -= 0x00000100 : 42;
		key == KEY_C ? fol->fractal.color -= 0x00010000 : 42;
		fol->fractal.color == 0 ? fol->fractal.color = 0x00FFFFFF : 42;
	}
	else if (fol->tom_hook == 0)
	{
		key == KEY_Z ? fol->fractal.color += 0x00000001 : 42;
		key == KEY_X ? fol->fractal.color += 0x00000100 : 42;
		key == KEY_C ? fol->fractal.color += 0x00010000 : 42;
		fol->fractal.color > 0x00FFFFFF ? fol->fractal.color = 0 : 42;
	}
	key == KEY_UP ? fol->fractal.set.p1.y += 30 / fol->fractal.zoom : 42;
	key == KEY_DOWN ? fol->fractal.set.p1.y -= 30 / fol->fractal.zoom : 42;
	key == KEY_RIGHT ? fol->fractal.set.p1.x += 30 / fol->fractal.zoom : 42;
	key == KEY_LEFT ? fol->fractal.set.p1.x -= 30 / fol->fractal.zoom : 42;
	key == KEY_ESC ? exit(1) : 42;
	fol_select(fol);
	return (0);
}

int		key_hook(int key, t_fol_t *fol)
{
	if (key == KEY_N1 || key == KEY_N2 || key == KEY_N3 || key == KEY_ENTER)
	{
		fol->f_type = 0;
		key == KEY_N1 ? ft_memcpy(fol->progname, "mandelbrot", 15) : NULL;
		key == KEY_N2 ? ft_memcpy(fol->progname, "julia", 15) : NULL;
		key == KEY_N3 ? ft_memcpy(fol->progname, "burningship", 15) : NULL;
	}
	if (key == KEY_I && fol->fractal.i_max <= 50)
		fol->fractal.i_max += 10;
	else if (key == KEY_I)
		fol->fractal.i_max += 50;
	if (key == KEY_U && fol->fractal.i_max > 10 && fol->fractal.i_max <= 50)
		fol->fractal.i_max -= 10;
	else if (key == KEY_U && fol->fractal.i_max > 10)
		fol->fractal.i_max -= 50;
	if (key == KEY_SHIFT && fol->tom_hook == 0)
		fol->tom_hook = 1;
	else if (key == KEY_SHIFT && fol->tom_hook == 1)
		fol->tom_hook = 0;
	if (key == KEY_O && fol->julia == 0)
		fol->julia = 1;
	else if (key == KEY_O && fol->julia == 1)
		fol->julia = 0;
	fol_select(fol);
	return (0);
}

int		mouse_hook(int mousecode, int x, int y, t_fol_t *fol)
{
	if ((mousecode == 4 | mousecode == 1) && fol->fractal.zoom < 1e+16)
	{
		fol->fractal.set.p1.x = x / fol->fractal.zoom + fol->fractal.set.p1.x
								- x / (fol->fractal.zoom * 1.3);
		fol->fractal.set.p1.y = y / fol->fractal.zoom + fol->fractal.set.p1.y
								- y / (fol->fractal.zoom * 1.3);
		fol->fractal.zoom *= 1.3;
	}
	else if ((mousecode == 5 | mousecode == 2) && fol->fractal.zoom > 0.1)
	{
		fol->fractal.set.p1.x = (x / fol->fractal.zoom + fol->fractal.set.p1.x)
								- (x / (fol->fractal.zoom / 1.3));
		fol->fractal.set.p1.y = (y / fol->fractal.zoom + fol->fractal.set.p1.y)
								- (y / (fol->fractal.zoom / 1.3));
		fol->fractal.zoom /= 1.3;
	}
	fol_select(fol);
	return (0);
}

void	fol_mlx_crea(t_fol_t *fol)
{
	if (!(fol->mlx.mlx = mlx_init()))
		close_screen(NULL);
	if (!(fol->mlx.img = mlx_new_image(fol->mlx.mlx, WIN_X, WIN_Y)))
	{
		ft_memdel(fol->mlx.mlx);
		close_screen(NULL);
	}
	if (!(fol->mlx.win = mlx_new_window(fol->mlx.mlx, WIN_X, WIN_Y,
										"fract'ol")))
	{
		mlx_destroy_image(fol->mlx.mlx, fol->mlx.img);
		ft_memdel(fol->mlx.mlx);
		close_screen(NULL);
	}
	fol->mlx.data_addr = (int32_t *)mlx_get_data_addr(fol->mlx.img,
			&fol->mlx.bits_per_pixel, &fol->mlx.line_size, &fol->mlx.endian);
}
