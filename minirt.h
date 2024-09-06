/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:32:15 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/05 16:07:40 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "fdf.h"
# include "libft.h"
# include "vec.h"
# include <math.h>

typedef t_vec	t_point;

typedef struct s_line
{
	t_vec		r0;
	t_vec		v;
}				t_line;

typedef t_line	t_plane;

typedef struct s_sphere
{
	t_point		pos;
	float		r;
}				t_sphere;

typedef struct s_cylinder
{
	t_point		pos;
	float		r;
	float		r_square;
	t_vec		axis;
	float		h;
	t_plane		top;
	t_plane		bottom;
}				t_cylinder;

typedef struct s_shape
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_color		color;
	char		texture;
}				t_shape;

typedef struct s_img_dim
{
	int			w;
	int			h;
}				t_img_dim;

typedef struct s_camera
{
	t_point		view_point;
	t_vec		orientation;
	float		fov;
}				t_camera;

// lightsource
typedef struct s_light
{
	t_point		pos;
	t_color		color;
}				t_light;

typedef struct s_ray
{
	t_vec		r0;
	t_vec		v;
	t_color		color;
}				t_ray;

typedef struct s_hit
{
	float		lambert;
	float		distance;
	t_vec		hit_point;
}				t_hit;

typedef struct s_state
{
	t_camera	cam;
	t_img_dim	dim;
	t_vec		cam_x;
	t_vec		cam_y;
	t_vec		cam_z;
	t_shape		**shapes;
	t_light		lights[10];
	int			n_shapes;
}				t_state;

t_state			*state(void);
void			init_state(void);
void			print_state(void);

// shapes
t_shape			*put_sphere(t_point pos, t_color color, float r);
t_hit			hit_sphere(t_sphere sphere, t_ray ray);
t_shape			*put_cylinder(t_point pos, t_vec axis, t_color color, float r,
					float h);
t_hit			hit_cylinder(t_cylinder cylinder, t_ray ray);
t_hit			hit_plane(t_plane plane, t_ray ray);
t_shape			*put_plane(t_point pos, t_vec normal, t_color color);

// camera
t_ray			create_camera_ray(int i, int j);
void			set_camera_vectors(void);

// tracing
t_hit			ray_hit(t_shape *s, t_ray ray);
int				minimum_distance(t_hit *distances, int n);
void			ray_color(t_ray *ray);
t_vec			ray_in_t(t_ray r, float t);

// test views
void			put_test1_view(void);
void			put_test2_view(void);
void			put_camera_above(void);
void			put_light_above(void);
void			put_camera_diagonal(void);
void			put_red_sphere_x(int i);
void			put_blue_sphere_y(int i);
void			put_yz_plane(int i);
void			put_bottom_plane(int i);

// light sources
t_ray			light_to_shape(float time, t_ray camera_ray, t_light light_src);

// shape utils
float			solve_quadratic(float a, float b, float c);
#endif