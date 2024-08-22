/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:34:58 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/08 12:40:53 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atohex(char *hex_str)
{
	int		res;
	char	*iter;
	char	base[17];

	ft_strlcpy(base, "0123456789ABSDEF", 17);
	iter = hex_str + 2;
	res = 0;
	while (*iter)
	{
		res = res * 16 + (ft_strchr(base, ft_toupper((int)*iter)) - base);
		iter ++;
	}
	return (res);
}

t_dim	set_dimensions(int file)
{
	char	*line;
	char	**words;
	int		max_words;
	int		h;
	int		w;

	w = 0;
	h = 0;
	max_words = 0;
	line = NULL;
	while (line || h == 0)
	{
		line = get_next_line(file);
		if (!line)
			break ;
		h++;
		words = ft_split(line, ' ');
		w = count_size_and_free(words);
		if (w > max_words)
			max_words = w;
		free(words);
		free(line);
	}
	return ((t_dim){.x = max_words, .y = h});
}

t_p	get_coefficients(t_vars *v, int border)
{
	t_p	coeff;
	int	z_max;

	coeff.x = (float)(v->w_dims.x - 2 * border) / (v->set->size.x - 1);
	coeff.y = (float)(v->w_dims.y - 2 * border) / (v->set->size.y - 1);
	if (coeff.x > coeff.y)
		coeff.x = coeff.y;
	z_max = get_z_max(*v->set);
	if (!z_max)
		z_max = 1;
	if (v->set->size.x / 5 >= 1)
		coeff.z = coeff.x / z_max * (v->set->size.x / 5);
	else
		coeff.z = coeff.x / z_max * 2;
	v->w_dims.z = coeff.z * z_max;
	return (coeff);
}

void	scale_reference_pts(t_vars *v, int border)
{
	int			i;
	int			j;
	t_p			coeff;

	coeff = get_coefficients(v, border);
	j = -1;
	while (++j < v->set->size.y)
	{
		i = -1;
		while (++i < v->set->size.x)
		{
			(*v->set->pts_0)[j][i].x = coeff.x * i + border;
			(*v->set->pts_0)[j][i].y = coeff.x * j + border;
			(*v->set->pts_0)[j][i].z = coeff.z * (*v->set->pts_0)[j][i].z;
			(*v->set->pts_0)[j][i].z0 = (*v->set->pts_0)[j][i].z;
		}
	}
}

void	get_map(char const *input_path, t_vars *v, int border)
{
	int	file;

	v->set = ft_calloc(sizeof(t_pt_set), 1);
	file = open(input_path, O_RDONLY);
	if (file > 0)
		v->set->size = set_dimensions(file);
	if (!v->set->size.x)
	{
		ft_printf("Invalid map\n");
		collect_pts_garbage(v);
		free(v);
		exit(1);
	}
	v->has_colors = 0;
	close(file);
	file = open(input_path, O_RDONLY);
	v->set->pts_0 = get_pts(file, v);
	close(file);
	scale_reference_pts(v, border);
	v->set->pts = pts_dup(v->set->size, *v->set->pts_0);
	v->set->dr = ft_calloc(1, sizeof(t_p));
	*v->set->dr = (t_p){.x = 0, .y = 0};
	shift_to_position(v);
	center_origin(v);
}
