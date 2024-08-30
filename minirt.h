/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:32:15 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/30 14:00:12 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "fdf.h"
# include "libft.h"
# include "vec.h"
# include <math.h>

typedef t_vec	t_point;

typedef struct s_sphere
{
	t_point		position;
	float		radius;
}				t_sphere;

typedef struct s_shape
{
	t_sphere	*sphere;
	t_sphere	*plane;
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

typedef struct s_line
{
	t_vec		r0;
	t_vec		v;
}				t_line;

typedef t_line	t_plane;

typedef struct s_ray
{
	t_vec		r0;
	t_vec		v;
	t_color		color;
}				t_ray;

typedef struct s_state
{
	t_camera	cam;
	t_img_dim	dim;
	t_vec		cam_x;
	t_vec		cam_y;
	t_vec		cam_z;
	t_shape		**shapes;
	int			n_shapes;
}				t_state;

t_state			*state(void);
void			init_state(void);
void			print_state(void);

// shapes
t_shape			*put_sphere(t_point position, t_color color, float radius);
float			hit_sphere(t_sphere sphere, t_ray ray);

// camera
t_ray			*create_camera_ray(int i, int j);
void			set_camera_vectors(void);

#endif