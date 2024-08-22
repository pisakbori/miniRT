/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:47:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/07 12:54:36 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <libft.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdio.h>
# include <math.h>

enum {
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
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}	t_data;

typedef struct s_hsv_color
{
	float	h;
	float	s;
	float	v;
}	t_hsv;

typedef struct s_rgb_color
{
	float	r;
	float	g;
	float	b;
}	t_rgb;

typedef struct s_p
{
	float	x;
	float	y;
	float	z;
	float	z0;
	t_hsv	color;
}	t_p;

typedef struct s_line_params
{
	t_p		*d;
	t_p		*s;
	t_p		*p0;
	float	*error;
	t_hsv	color_min;
	t_hsv	color_max;
}		t_line_params;

typedef struct s_w_dims
{
	int	x;
	int	y;
	int	z;
}	t_dim;

typedef struct pt_set
{
	t_p		***pts;
	t_p		***pts_0;
	t_dim	size;
	t_p		*dr;
}	t_pt_set;

typedef struct s_vars
{
	t_data		img;
	void		*mlx;
	void		*window;
	t_pt_set	*set;
	t_hsv		c_min;
	t_hsv		c_max;
	t_dim		w_dims;
	int			has_colors;
}	t_vars;

void		get_map(const char *input_path, t_vars *v, int border);
void		paint_line(t_p p1, t_p p2, t_vars *args);
void		center_origin(t_vars *vars);
void		shift_to_position(t_vars *v);
t_p			***pts_dup(t_dim pts_dim, t_p **src_pts);
void		pts_cpy(t_dim pts_dim, t_p **src_pts, t_p ***dest_pts);
void		rotate(t_vars *vars, char sx, char sy, char sz);
void		shift(t_vars *v, char sx, char sy);
t_p			***get_pts(int file, t_vars *vars);
void		img_mlx_pixel_put(t_vars v, t_p p, int color);
int			get_color(float z, float z_min, float z_max, t_vars v);
t_hsv		rgb_to_hsv(	t_rgb	rgb_c);
t_rgb		int_to_rgb(int color);
int			rgb_to_int(t_rgb c);
t_rgb		hsv_to_rgb(t_hsv c);
int			asc(float a, float b);
int			desc(float a, float b);
float		compare(float a, float b, float c, int (*compare)(float, float));
int			get_z_max(t_pt_set set);
void		collect_pts_garbage(t_vars *v);
int			handle_key_press(int k, t_vars *vars);
int			put_map_to_window(t_vars *vars);
int			close_win(t_vars *vars);
int			count_size_and_free(char **words);
int			ft_atohex(char *hex_str);
int			arr_len(char **arr);
void		free_line_params(t_line_params *var);
#endif