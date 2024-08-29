/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:32:15 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/08/29 10:44:23 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "fdf.h"
# include "libft.h"
# include "vec.h"

typedef t_vec		t_point;

/// @brief
// view_point: camera position
// orientation: normalized vector. Coordinates in range [-1,1]
// fov :Horizontal field of view in degrees in range [0,180]

// typedef struct s_viewport
// {
// 	float			viewport_h;
// 	float			viewport_w;
// 	t_vec			*viewport_u;
// 	t_vec			*viewport_v;
// }					t_viewport;

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
}					t_camera;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	brightness;
}					t_color;

typedef struct s_sphere
{
	t_point			position;
	float			radius;
	t_color			color;
	char			texture;
}					t_sphere;

typedef struct s_line
{
	t_vec			r0;
	t_vec			v;
}					t_line;

typedef t_line		t_plane;

typedef struct s_ray
{
	t_vec			r0;
	t_vec			v;
	t_color			color;
}					t_ray;

typedef struct s_state
{
	t_camera		cam;
	t_img_dim		dim;
	t_vec			cam_x;
	t_vec			cam_y;
	t_vec			cam_z;
}					t_state;

t_state				*state(void);
void				init_state(void);
void				print_state(void);

#endif