/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:47:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/09/09 13:58:14 by bpisak-l         ###   ########.fr       */
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
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}			t_data;

typedef struct s_w_dims
{
	int		x;
	int		y;
	int		z;
}			t_dim;

typedef struct s_vars
{
	t_data	img;
	void	*mlx;
	void	*window;
	t_dim	w_dims;
}			t_vars;

void		collect_mlx_garbage(t_vars *v);

#endif