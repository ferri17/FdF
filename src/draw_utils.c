/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:12:19 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/08 02:55:26 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	draw_map_mode(t_mlx *data, t_map *map, int i)
{
	if (map->mode == WIRE)
	{
		map->line.start = map->obj[i];
		if (i % map->x_size < map->x_size - 1)
		{
			map->line.end = map->obj[i + 1];
			bresenham(data, data->map.line);
		}
		if (i < map->size - map->x_size)
		{
			map->line.end = map->obj[i + map->x_size];
			bresenham(data, data->map.line);
		}
	}
	else
		draw_dot(data, map->obj[i]);
}

void	my_string_put(t_mlx *data, int x, int y, char *txt)
{
	mlx_string_put(data->mlx, data->mlx_win, x, y, data->map.theme[TEXT], txt);
}

int	get_color_gradient(int startcolor, int endcolor, int len, int progress)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	if (len == 0)
		len++;
	increment[0] = (double)((R(endcolor)) - (R(startcolor))) / (double)len;
	increment[1] = (double)((G(endcolor)) - (G(startcolor))) / (double)len;
	increment[2] = (double)((B(endcolor)) - (B(startcolor))) / (double)len;
	new[0] = (R(startcolor)) + round(progress * increment[0]);
	new[1] = (G(startcolor)) + round(progress * increment[1]);
	new[2] = (B(startcolor)) + round(progress * increment[2]);
	newcolor = RGB(new[0], new[1], new[2]);
	return (newcolor);
}

void	set_color(t_image *img, int pixel, int color)
{
	if (img->endian == 1)
	{
		img->buffer[pixel + 0] = A(color);
		img->buffer[pixel + 1] = R(color);
		img->buffer[pixel + 2] = G(color);
		img->buffer[pixel + 3] = B(color);
	}
	else if (img->endian == 0)
	{
		img->buffer[pixel + 0] = B(color);
		img->buffer[pixel + 1] = G(color);
		img->buffer[pixel + 2] = R(color);
		img->buffer[pixel + 3] = A(color);
	}
}

void	draw_dot(t_mlx *data, t_point obj)
{
	int	i;
	int	x;
	int	y;
	int	color;

	x = round((int)obj.axis[X]);
	y = round((int)obj.axis[Y]);
	color = round((int)obj.color);
	i = 0;
	while (i - LEN_DOT < LEN_DOT)
		my_put_pixel(data, x + (i++ - LEN_DOT), y, color);
	i = 0;
	while (i - LEN_DOT < LEN_DOT)
		my_put_pixel(data, x, y + (i++ - LEN_DOT), color);
}
