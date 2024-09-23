/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:32:15 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/23 17:22:24 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "mlx_utils.h"
# include "vec.h"
# include <math.h>
# include <stdio.h>

# define K_SPECULAR 1.f
# define K_DIFFUSE 1.f

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1024
# endif

# ifndef BONUS
#  define BONUS 0
# endif

typedef t_vec		t_point;

typedef struct s_counter
{
	int				count_a;
	int				count_c;
	int				count_l;
}					t_counter;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
	float			brightness;
}					t_color;

typedef struct s_line
{
	t_vec			r0;
	t_vec			v;
}					t_line;

typedef t_line		t_plane;

typedef struct s_sphere
{
	t_point			pos;
	float			r;
}					t_sphere;

typedef struct s_cylinder
{
	t_point			pos;
	float			r;
	float			r_square;
	t_vec			axis;
	float			h;
	t_plane			top;
	t_plane			bottom;
}					t_cylinder;

typedef struct s_shape
{
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	t_color			color;
}					t_shape;

typedef struct s_img_dim
{
	int				w;
	int				h;
}					t_img_dim;

typedef struct s_camera
{
	t_point			view_point;
	t_vec			orientation;
	float			fov;
	int				fov_deg;
}					t_camera;

// lightsource
typedef struct s_light
{
	t_point			pos;
	t_color			color;
}					t_light;

typedef struct s_ambient_light
{
	t_color			color;
}					t_ambient_light;

typedef struct s_ray
{
	t_vec			r0;
	t_vec			v;
	t_color			color;
}					t_ray;

typedef struct s_hit
{
	t_vec			normal;
	t_vec			surface_to_light;
	float			t;
	t_vec			hit_point;
}					t_hit;

typedef struct s_state
{
	t_camera		cam;
	t_img_dim		dim;
	t_vec			cam_x;
	t_vec			cam_y;
	t_vec			cam_z;
	t_list			*shapes;
	t_list			*lights;
	float			t;
	t_ambient_light	ambient;
}					t_state;

// parse
void				parse_input(int argc, char **argv, t_counter *counter);
void				parse_input_line(char *line, t_counter *counter);
void				put_shape_node(t_shape *shape);
void				put_light_node(t_light *light);
void				parse_camera(char **d);
void				parse_light(char **d);
void				parse_cylinder(char **d);
void				parse_sphere(char **d);
void				parse_plane(char **d);
void				put_shape_node(t_shape *shape);
void				put_light_node(t_light *light);
t_vec				parse_vector(char *str);
t_color				parse_color(char *str);
void				parse_ambient(char **d);

// colors
int					rgb_to_int(t_color c);
void				multiply_color(t_color *dst, t_color src);
t_color				sum_color(t_color c1, t_color c2);
void				scale_color(t_color *color, float s);
void				gamma_correct(t_color *c);

t_state				*state(void);
void				init_state(void);

// debug
void				print_color(t_color color);
void				print_vec(t_vec vector);
void				print_ambient(t_ambient_light a);
void				print_camera(t_camera c);
void				print_light(t_light c);
void				print_state(void);

// shapes
t_shape				*put_sphere(t_point pos, t_color color, float r);
t_hit				hit_sphere(t_sphere sphere, t_ray ray);
t_shape				*put_cylinder(t_cylinder *s, t_color color);
t_cylinder			*get_cylinder(t_point pos, t_vec axis, float d, float h);
void				translate_cylinder(t_cylinder *s, t_vec v);
void				rotate_cylinder(t_cylinder *s, t_vec axis, int deg);
float				get_t(t_vec v_a, t_vec ra0, t_cylinder cylinder);
t_hit				hit_cylinder(t_cylinder cylinder, t_ray ray);
t_hit				hit_plane(t_plane plane, t_ray ray);
t_shape				*put_plane(t_point pos, t_vec normal, t_color color);

// camera
t_ray				create_camera_ray(int i, int j);
void				set_camera_vectors(void);

// tracing
t_hit				ray_hit(t_shape s, t_ray ray);
int					index_of_closest(t_hit *ts, int n);
void				ray_color(t_ray *ray);
t_vec				ray_in_t(t_ray r, float t);
float				get_illumination(t_vec from_camera, t_hit hit);

// light sources
t_ray				light_to_shape(float time, t_ray camera_ray,
						t_vec light_pos);

// translate,rotate
void				translate_camera(t_vec v);
void				translate_object(int i, t_vec v);
void				translate_light(int i, t_vec v);
void				rotate_camera(t_vec v, int deg);
void				rotate_object(int i, t_vec v, int deg);

// shape utils
float				solve_quadratic(float a, float b, float c);

// mlx_utils
int					handle_key_press(int k, t_vars *vars);
int					close_win(t_vars *vars);
int					put_picture_to_window(t_vars *vars);

#endif