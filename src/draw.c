/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:03:56 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/23 12:02:58 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	apply_transformations(t_map *map)
{
	float	rotation_matrix_x[3][3];
	float	rotation_matrix_y[3][3];
	float	rotation_matrix_z[3][3];
	int		i;

	init_rotate_x(map, rotation_matrix_x);
	init_rotate_y(map, rotation_matrix_y);
	init_rotate_z(map, rotation_matrix_z);
	i = 0;
	while (i < map->size)
	{
		map->obj[i].axis[Z] *= map->z_resize;
		mult_matrix(&map->obj[i], rotation_matrix_x);
		mult_matrix(&map->obj[i], rotation_matrix_y);
		mult_matrix(&map->obj[i], rotation_matrix_z);
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
			my_put_pixel(data, x, y, bg_color);
			x++;
		}
		y++;
	}
}

void	fill_background_menu(t_mlx *data, int menu_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < MENU_W)
		{
			my_put_pixel(data, x, y, menu_color);
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
