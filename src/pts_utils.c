/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pts_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:11:06 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/07 12:46:52 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_z_and_color(t_p *pt, char *text, int *has_color)
{
	int		color;
	float	z;
	char	**pt_values;

	color = 0xFFFFFF;
	pt_values = ft_split(text, ',');
	z = (float)ft_atoi(pt_values[0]);
	if (pt_values[1])
	{
		*has_color = 1;
		color = ft_atohex(pt_values[1]);
	}
	pt->z = z;
	pt->color = rgb_to_hsv(int_to_rgb(color));
	count_size_and_free(pt_values);
	free(pt_values);
}

t_p	*line_to_point_row(char *line, t_vars *v, int h)
{
	t_p		*pts;
	char	**words;
	int		i;

	pts = (t_p *) ft_calloc(v->set->size.x, sizeof(t_p));
	words = ft_split(line, ' ');
	i = -1;
	while (++i < v->set->size.x)
	{
		if (i >= arr_len(words))
			set_z_and_color(&pts[i], "0", &v->has_colors);
		else
		{
			set_z_and_color(&pts[i], words[i], &v->has_colors);
			free(words[i]);
		}
		pts[i].x = i;
		pts[i].y = h;
	}
	free(words);
	return (pts);
}

t_p	***get_pts(int file, t_vars *v)
{
	t_p			**pts;
	t_p			***p_pts;
	char		*line;
	int			i;

	i = -1;
	p_pts = ft_calloc(1, sizeof(t_p **));
	pts = (t_p **)ft_calloc(v->set->size.y, sizeof(t_p *));
	while (++i < v->set->size.y)
	{
		line = get_next_line(file);
		pts[i] = line_to_point_row(line, v, i);
		free(line);
	}
	*p_pts = pts;
	return (p_pts);
}

t_p	***pts_dup(t_dim pts_dim, t_p **src_pts)
{
	t_p			**pts;
	t_p			***p_pts;
	int			i;
	int			j;

	i = -1;
	if (!src_pts || !*src_pts)
		return (NULL);
	p_pts = (t_p ***)ft_calloc(1, sizeof(t_p **));
	pts = (t_p **)ft_calloc(pts_dim.y, sizeof(t_p *));
	while (++i < pts_dim.y)
	{
		pts[i] = (t_p *) ft_calloc(pts_dim.x, sizeof(t_p));
		j = -1;
		while (++j < pts_dim.x)
			pts[i][j] = src_pts[i][j];
	}
	*p_pts = pts;
	return (p_pts);
}

void	pts_cpy(t_dim pts_dim, t_p **src_pts, t_p ***dest_pts)
{
	int		i;
	int		j;

	if (!src_pts || !*src_pts)
		return ;
	i = -1;
	while (++i < pts_dim.y)
	{
		j = -1;
		while (++j < pts_dim.x)
			(*dest_pts)[i][j] = src_pts[i][j];
	}
}
