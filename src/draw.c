/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:03:56 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/05 22:33:25 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void	apply_transformations(t_map *map)
{
	int		i;

	i = 0;
	while (i < map->size)
	{
		map->obj[i].axis[Z] *= map->z_resize;
		mult_matrix(&map->obj[i], map->r_matrix.x);
		mult_matrix(&map->obj[i], map->r_matrix.z);
		mult_matrix(&map->obj[i], map->r_matrix.y);
		map->obj[i].axis[X] *= map->zoom;
		map->obj[i].axis[Y] *= map->zoom;
		map->obj[i].axis[Z] *= map->zoom;
		map->obj[i].axis[X] += map->translate[X];
		map->obj[i].axis[Y] += map->translate[Y];
		i++;
	}
}

void	draw_map(t_mlx *data, t_map *map)
{
	int	i;

	map->obj = (t_point *)malloc(sizeof(t_point) * map->size);
	if (!map->obj)
		close_program((void *)data, EXIT_FAILURE);
	ft_memcpy(map->obj, map->terrain, map->size * sizeof(t_point));
	apply_transformations(map);
	i = 0;
	while (i < map->size)
	{
		draw_map_mode(data, map, i);
		i++;
	}
}

void	fill_background(t_mlx *data, int bg_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (x < WIN_W2 && y < WIN_H2)  //DELTEEEEEEEEEEEEEEE
				my_put_pixel(data, x, y, BLUE_DARK);
			else
				my_put_pixel(data, x, y, bg_color);
			x++;
		}
		y++;
	}
}

int	my_put_pixel(t_mlx *data, int x, int y, int color)
{
	int	pixel;

	if (data->img.pixel_bits != 32)
		color = mlx_get_color_value(data->mlx, color);
	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return (1);
	pixel = (data->img.line_bytes * y) + (x * data->img.pixel_bits / 8);
	set_color(&data->img, pixel, color);
	return (0);
}
