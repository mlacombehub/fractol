/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:22:14 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/16 11:50:31 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fol_multithread(t_fol_t *fol)
{
	t_fol_t		tab[WIN_Y / W_THREAD];
	pthread_t	t[WIN_Y / W_THREAD];
	int			i;

	i = 0;
	while (i * W_THREAD < WIN_Y)
	{
		ft_memcpy((void*)&tab[i], (void*)fol, sizeof(t_fol_t));
		tab[i].fractal.offset.y = W_THREAD * i;
		tab[i].fractal.y_max = W_THREAD * (i + 1);
		fol->f_type == 1 ? ft_puterror(pthread_create(&t[i], NULL,
			fol_mandelbrot, &tab[i]), "error creating threads") : 42;
		fol->f_type == 2 ? ft_puterror(pthread_create(&t[i], NULL,
			fol_julia, &tab[i]), "error creating threads") : 42;
		fol->f_type == 3 ? ft_puterror(pthread_create(&t[i], NULL,
			fol_burningship, &tab[i]), "error creating threads") : 42;
		i++;
	}
	while (i--)
		ft_puterror(pthread_join(t[i], NULL), "error joining threads");
	mlx_put_image_to_window(fol->mlx.mlx, fol->mlx.win, fol->mlx.img, 0, 0);
}

void	fol_select(t_fol_t *fol)
{
	if (ft_strequ(fol->progname, "mandelbrot"))
		!fol->f_type ? fol_mandelbrot_init(fol) : 42;
	else if (ft_strequ(fol->progname, "julia"))
		!fol->f_type ? fol_julia_init(fol) : 42;
	else if (ft_strequ(fol->progname, "burningship"))
		!fol->f_type ? fol_burningship_init(fol) : 42;
	else
	{
		ft_putendl_fd("usage : ./fractol [mandelbrot | julia | burningship]\n",
						2);
		exit(1);
	}
	fol_multithread(fol);
	fol->RGB_c = ft_itoa_base(fol->fractal.color, 16);
	mlx_string_put(fol->mlx.mlx, fol->mlx.win, 10, 10, 0xFF0000, fol->RGB_c);
}

void	fol_putpixel(t_fol_t *fol, t_point_t p, uint32_t color)
{
	int32_t	i;

	if ((p.x >= 0 && p.x < WIN_X) || (p.y >= 0 && p.y < WIN_Y))
	{
		color = mlx_get_color_value(fol->mlx.mlx, color);
		i = p.x + p.y * (WIN_X);
		fol->mlx.data_addr[i] = color;
	}
}

void	fol_calc(t_fol_t *fol, t_set_t set)
{
	double	tmp;

	fol->fractal.i = 0;
	while (sqrt(set.z.r * set.z.r + set.z.i * set.z.i) < 4 && fol->fractal.i
			< fol->fractal.i_max)
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
		fol->fractal.i -= log(log(sqrt(set.z.r * set.z.r +
							set.z.i * set.z.i))) / log(2);
		fol->fractal.i = ((NB_COLOR - 1) * fol->fractal.i)
							/ fol->fractal.i_max;
		fol_putpixel(fol, fol->fractal.offset,
						fol->fractal.color * fol->fractal.i);
	}
}

int		main(int ac, char **av)
{
	t_fol_t	*fol;
	int32_t	i;

	i = 0;
	ft_puterror((ac == 1 || ac > 2),
					"usage : ./fractol [mandelbrot | julia | burningship]\n");
	if (!(fol = (t_fol_t *)malloc(sizeof(t_fol_t))))
		return (-1);
	ft_bzero(fol, sizeof(fol));
	fol_mlx_crea(fol);
	if (!(fol->progname = (char *)malloc(sizeof(char) * 15)))
		exit(1);
	ft_bzero(fol->progname, 15);
	fol->f_type = 0;
	ft_strcpy(fol->progname, av[1]);
	fol_select(fol);
	mlx_hook(fol->mlx.win, 17, 0L, close_screen, fol);
	mlx_mouse_hook(fol->mlx.win, mouse_hook, fol);
	mlx_key_hook(fol->mlx.win, key_hook, fol);
	mlx_hook(fol->mlx.win, 2, 1, hook, fol);
	mlx_loop(fol->mlx.mlx);
	return (1);
}
