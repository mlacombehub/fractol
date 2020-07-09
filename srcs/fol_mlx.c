/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fol_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:36:32 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/08 17:25:35 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		close_screen(void *param)
{
	(void)param;
	exit(1);
	return (0);
}

int		key_hook(int keycode, t_fol_t *fol)
{
	keycode == KEY_ESC ? exit(1) : 42;
	keycode == KEY_UP ? fol->fractal.offset.y -= 30 / fol->fractal.zoom : 42;
	keycode == KEY_DOWN ? fol->fractal.offset.y += 30 / fol->fractal.zoom : 42;
	keycode == KEY_RIGHT ? fol->fractal.offset.x -= 30 / fol->fractal.zoom : 42;
	keycode == KEY_LEFT ? fol->fractal.offset.x += 30 / fol->fractal.zoom : 42;
	keycode == KEY_I ? fol->fractal.i_max += 50 : 42;
	keycode == KEY_U ? fol->fractal.i_max -= 50 : 42;
	// ft_putendl_nbr(keycode);
	fol_calc(fol);
	return(0);
}

int		mouse_hook(int mousecode, t_point_t p, t_fol_t *fol)
{
	ft_putendl_nbr(mousecode);
	if (mousecode == 4 | mousecode == 1)
	{
		// fol->fractal.set.p1.x = p.x / fol->fractal.zoom + fol->fractal.set.p1.x - p.x / (fol->fractal.zoom * 1.3);
		// fol->fractal.set.p1.y = p.y / fol->fractal.zoom + fol->fractal.set.p1.y - p.y / (fol->fractal.zoom * 1.3);
		// fol->fractal.zoom *= 1.3;
		// fol->fractal.i_max++;
		fol->fractal.zoom *= 1.01;
		fol->fractal.offset.x = (fol->fractal.offset.x + ((WIN_X - (WIN_X / 1.01)) / 2) +
		((p.x) - WIN_X / 2) * (1 - (1 / 1.01))) * 1.01;
		fol->fractal.offset.y = (fol->fractal.offset.y + ((WIN_Y - (WIN_Y / 1.01)) / 2) +
		((p.y) - WIN_Y / 2) * (1 - (1 / 1.01))) * 1.01;
	}
	else if (mousecode == 5 | mousecode == 2)
	{
		// fol->fractal.set.p1.x = (p.x / fol->fractal.zoom + fol->fractal.set.p1.x) - (p.x / (fol->fractal.zoom / 1.3));
		// fol->fractal.set.p1.y = (p.y / fol->fractal.zoom + fol->fractal.set.p1.y) - (p.y / (fol->fractal.zoom / 1.3));
		// fol->fractal.zoom /= 1.3;
		// fol->fractal.i_max--;
		fol->fractal.zoom *= 1.01;
		fol->fractal.offset.x = fol->fractal.offset.x / 1.01 - ((WIN_X - (WIN_X / 1.01)) / 2) /
		1.01 - (p.x - WIN_X / 2) * (1 - (1 / 1.01)) + 1.01;
		fol->fractal.offset.y = fol->fractal.offset.y / 1.01 - ((WIN_Y - (WIN_Y / 1.01)) / 2) /
		1.01 - (p.y - WIN_Y / 2) * (1 - (1 / 1.01)) + 1.01;
	}
	fol_calc(fol);
	return(0);
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
	if (!(fol->mlx.win = mlx_new_window(fol->mlx.mlx, WIN_X, WIN_Y, "fract'ol")))
	{
		mlx_destroy_image(fol->mlx.mlx, fol->mlx.img);
		ft_memdel(fol->mlx.mlx);
		close_screen(NULL);
	}
	fol->mlx.data_addr = (int32_t *)mlx_get_data_addr(fol->mlx.img, &fol->mlx.bits_per_pixel,
		&fol->mlx.line_size, &fol->mlx.endian);
}
