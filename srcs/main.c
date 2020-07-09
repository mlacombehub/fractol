/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:22:14 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/09 18:17:55 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fol_calc(t_fol_t *fol)
{

	if (ft_strequ(fol->progname, "mandelbrot"))
	{
		!fol->f_type ? fol_init_mandelbrot(fol) : 0;
		// fol_mandelbrot_calc(fol, fol->fractal.set);
		fol_mandelbrot_thread(fol);
	}
	// else if (ft_strequ(fol->progname, "julia"))
	// {
	// 	fol_init_julia(fol);
	// 	fol_julia_thread(fol);
	// }
	else if (ft_strequ(fol->progname, "other"))
	{
		fol->f_type ? fol_init_mandelbrot(fol) : 0;
		fol_mandelbrot_thread(fol);
	}
	else
	{
		ft_putendl_fd("usage : ./fol [mandelbrot | julia | other]\n", 2);
		exit(1);
	}
	mlx_put_image_to_window(fol->mlx.mlx, fol->mlx.win, fol->mlx.img, 0, 0);
}

void	fol_param(t_fol_t *fol, int ac, char **av)
{
	ft_puterror(ac > 2, "usage : ./fol [mandelbrot | julia | other]\n");
	fol->progname = (char *)malloc(sizeof(char) * ft_strlen(av[1]) + 1);
	fol->f_type = 0;
	ft_strcpy(fol->progname, av[1]);
	fol_calc(fol);
}

int 	main(int ac, char **av)
{
	t_fol_t	*fol;
	int32_t	i;

	i = 0;
	if (!(fol = (t_fol_t *)malloc(sizeof(t_fol_t))))
		return (-1);
	ft_bzero(fol, sizeof(fol));
	fol_mlx_crea(fol);
	fol_param(fol, ac, av);
	// mlx_hook(fol->mlx.win, 6, 1L < 6, mouse_julia, fol);
	mlx_hook(fol->mlx.win, 17, 0L, close_screen, fol);
	mlx_key_hook(fol->mlx.win, key_hook, fol);
	// mlx_mouse_hook(fol->mlx.win, mouse_hook, fol);
	mlx_loop(fol->mlx.mlx);
	return (1);
}
