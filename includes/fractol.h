/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:32:38 by mlacombe          #+#    #+#             */
/*   Updated: 2020/07/19 18:22:09 by mlacombe         ###   ########.fr       */
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

# define WIN_X 1000
# define WIN_Y 1000
# define NB_COLOR 0x0000FF
# define W_THREAD 5

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	int32_t		*data_addr;
	int32_t		bits_per_pixel;
	int32_t		endian;
	int32_t		line_size;
	char		alignment[4];
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
	t_cmplx_t	new_c;
}				t_set_t;

typedef struct	s_fractal
{
	t_set_t		set;
	t_point_t	offset;
	double		zoom;
	uint32_t	color;
	uint32_t	i;
	uint32_t	i_max;
	int32_t		y_max;
}				t_fractal_t;

typedef struct	s_fol
{
	t_fractal_t	fractal;
	t_mlx_t		mlx;
	char		*progname;
	char		tom_hook;
	char		f_type;
	char		julia;
	char		alignment[5];
}				t_fol_t;

int				hook(int keycode, t_fol_t *fol);
int				mouse_hook(int mousecode, int x, int y, t_fol_t *fol);
int				key_hook(int keycode, t_fol_t *fol);
void			fol_select(t_fol_t *fol);
void			fol_mandelbrot_init(t_fol_t *fol);
void			*fol_mandelbrot(void *tab);
void			fol_julia_init(t_fol_t *fol);
void			*fol_julia(void *tab);
void			fol_burningship_init(t_fol_t *fol);
void			*fol_burningship(void *tab);
void			fol_putpixel(t_fol_t *fol, t_point_t point, uint32_t color);
void			fol_calc(t_fol_t *fol, t_set_t set);
int				mouse_julia(int x, int y, t_fol_t *fol);
void			fol_mlx_crea(t_fol_t *fol);
int				close_screen(void *param);

#endif
