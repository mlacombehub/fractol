/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:32:38 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/09 17:56:33 by mlacombe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include "keymap.h"
# include <stdlib.h>
# include <math.h>
# include <pthread.h>

# include <stdio.h>

#define WIN 1000
#define WIN_X 1000
#define WIN_Y 1000
#define NB_COLOR 265
#define W_THREAD 5
#define I_THREAD 200

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	int32_t		*data_addr;
	int32_t		bits_per_pixel;
	int32_t		endian;
	int32_t		line_size;
}				t_mlx_t;

typedef struct	s_vec2
{
	double		x;
	double		y;
}				t_vec2_t;

typedef struct	s_cmplx
{
	double		r;
	double		i;
}				t_cmplx_t;

typedef struct	s_set
{
	t_vec2_t	p1;
	t_cmplx_t	z;
	t_cmplx_t	c;
}				t_set_t;

typedef struct	s_fractal
{
	t_set_t		set;
	int			julia_mouse;
	t_point_t	offset;
	double		zoom;
	int			color;
	int			i;
	int			i_max;
	int			y_max;
}				t_fractal_t;

typedef struct	s_fol
{
	char		*progname;
	t_mlx_t		mlx;
	t_fractal_t	fractal;
	char		f_type;
}				t_fol_t;

int		mouse_hook(int mousecode, t_point_t p, t_fol_t *fol);
int		key_hook(int keycode, t_fol_t *fol);
void	fol_calc(t_fol_t *fol);
void	fol_init_mandelbrot(t_fol_t *fol);
void	fol_mandelbrot_calc(t_fol_t *fol, t_set_t set);
void	fol_mandelbrot_thread(t_fol_t *fol);
void	fol_mlx_crea(t_fol_t *fol);
int		close_screen(void *param);

#endif
