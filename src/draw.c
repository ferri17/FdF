/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:03:56 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/20 17:42:22 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"




#include <stdio.h>




void	mult_matrix(t_point *point, float (*matrix)[3])
{
	int		i;
	int		j;
	int		size;
	float	temp[3];

	temp[X] = point->axis[X];
    temp[Y] = point->axis[Y];
    temp[Z] = point->axis[Z];
	i = 0;
	while (i < MATRIX_SIZE)
	{
		point->axis[i] = 0;
		j = 0;
		while (j < MATRIX_SIZE)
		{
			//printf("before %.2f\n", point.axis[i]);
			point->axis[i] += temp[j] * matrix[i][j];
			//printf("after %.2f\n\n", point.axis[i]);
			j++;
		}
		i++;
	}
}

void	apply_transformations(t_map *map)
{
	int	i;
	float rotate_x_matrix[3][3];
	float	angle;

	//ft_printf("rotate x %i\n", map->rotate[X]);
	angle = map->rotate[X] * (M_PI / 180);
	rotate_x_matrix[0][0] = 1;
	rotate_x_matrix[0][1] = 0;
	rotate_x_matrix[0][2] = 0;
	rotate_x_matrix[1][0] = 0;
	rotate_x_matrix[1][1] = cos(angle);
	rotate_x_matrix[1][2] = -sin(angle);
	rotate_x_matrix[2][0] = 0;
	rotate_x_matrix[2][1] = sin(angle);
	rotate_x_matrix[2][2] = cos(angle);

	i = 0;
	//printf("y %.2f\n\n", map->obj[i].axis[Y]);
	while (i < map->size)
	{
		mult_matrix(&map->obj[i], rotate_x_matrix);
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

	map->obj = (t_point *)malloc(sizeof(t_point) * map->size); //free obj before creating new one
	if (!map->obj)
		close_program((void *)data, EXIT_FAILURE);
	ft_memcpy(map->obj, map->terrain, map->size * sizeof(t_point));
	apply_transformations(map);
	i = 0;
	while (i < map->size)
	{
		map->line.start.axis[X] = map->obj[i].axis[X];
		map->line.start.axis[Y] = map->obj[i].axis[Y];
		map->line.end.axis[X] = map->obj[i + 1].axis[X];
		map->line.end.axis[Y] = map->obj[i].axis[Y];
		if (i % map->x_size < map->x_size -1)
			bresenham(data, data->map.line, data->map.terrain[i].color,
				data->map.terrain[i + 1].color);
		map->line.end.axis[X] = map->obj[i].axis[X];
		map->line.end.axis[Y] = map->obj[i + map->x_size].axis[Y];
		if (i < map->size - map->x_size)
			bresenham(data, data->map.line, data->map.terrain[i].color,
				data->map.terrain[i+ 1].color);
		i++;
	}
}

void	fill_background(t_mlx *data, int color1, int color2)
{
	int	x;
	int	y;
	int	k;
	int	color;
	
	if (data->img.pixel_bits != 32)
	{
		color1 = mlx_get_color_value(data->mlx, color1);
		color2 = mlx_get_color_value(data->mlx, color2);
	}
	k = 0;
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			color = get_color_gradient(color1, color2, WIN_W * WIN_H, k);
			my_put_pixel(&data->img, x, y, color);
			x++;
			k++;
		}
		y++;
	}
}

int	my_put_pixel(t_image *img, int x, int y, int color)
{
	int	pixel;

	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return (1);
	pixel = (img->line_bytes * y) + (x * img->pixel_bits / 8);
	set_color(img, pixel, color);
	return (0);
}
