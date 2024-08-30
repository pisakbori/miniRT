/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:47:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/30 11:02:12 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <dirent.h>
# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};
// bpp: bits per pixel
// ll: 	line_length
typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			ll;
	int			endian;
}				t_data;

typedef struct s_p
{
	float		x;
	float		y;
	float		z;
	float		z0;
}				t_p;

typedef struct s_line_params
{
	t_p			*d;
	t_p			*s;
	t_p			*p0;
	float		*error;
}				t_line_params;

typedef struct s_w_dims
{
	int			x;
	int			y;
	int			z;
}				t_dim;

typedef struct pt_set
{
	t_p			***pts;
	t_p			***pts_0;
	t_dim		size;
	t_p			*dr;
}				t_pt_set;

typedef struct s_vars
{
	t_data		img;
	void		*mlx;
	void		*window;
	t_pt_set	*set;
	int			color_min;
	int			color_max;
	t_dim		w_dims;
}				t_vars;

typedef struct s_hsv_color
{
	float		h;
	float		s;
	float		v;
}				t_hsv;

typedef struct s_rgb_color
{
	float		r;
	float		g;
	float		b;
}				t_rgb;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			brightness;
}				t_color;

void			get_map(const char *input_path, t_vars *v, int border);
void			center_origin(t_vars *vars);
void			pts_free(t_dim pts_dim, t_p ***pts);
int				get_color(float z, float z_max);
int				asc(float a, float b);
int				desc(float a, float b);
float			compare(float a, float b, float c, int (*compare)(float,
						float));
void			collect_pts_garbage(t_vars *v);
int				handle_key_press(int k, t_vars *vars);
int				put_map_to_window(t_vars *vars);
int				close_win(t_vars *vars);
void			normalize_color(t_color *c);
int				rgb_to_int(t_color c);
void			copy_color(t_color *dst, t_color src);
#endif