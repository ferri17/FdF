/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:03:56 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/21 16:24:16 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"


 void	draw_dot(t_image *img, t_point obj)
{
	int	x;
	int	y;
	int	color;

	x = round((int)obj.axis[X]);
	y = round((int)obj.axis[Y]);
	color = round((int)obj.color);

	my_put_pixel(img, x, y, color);
	my_put_pixel(img, x + 2, y, color);
	my_put_pixel(img, x + 3, y, color);
	my_put_pixel(img, x + 4, y, color);
	my_put_pixel(img, x - 1, y, color);
	my_put_pixel(img, x - 2, y, color);
	my_put_pixel(img, x - 3, y, color);
	my_put_pixel(img, x - 4, y, color);
	my_put_pixel(img, x, y + 1, color);
	my_put_pixel(img, x, y + 2, color);
	my_put_pixel(img, x, y + 3, color);
	my_put_pixel(img, x, y + 4, color);
	my_put_pixel(img, x, y - 1, color);
	my_put_pixel(img, x, y - 2, color);
	my_put_pixel(img, x, y - 3, color);
	my_put_pixel(img, x, y - 4, color);
}

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

void	init_matrix(float	matrix[3][3])
{
	matrix[0][0] = 0;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = 0;
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 0;
}

void	init_rotate_x(t_map *map, float rotation_matrix_x[3][3])
{
	float	angle_x;

	angle_x = RADIAN(map->rotate[X]);
	init_matrix(rotation_matrix_x);
	rotation_matrix_x[0][0] = 1;
	rotation_matrix_x[1][1] = cos(angle_x);
	rotation_matrix_x[1][2] = -sin(angle_x);
	rotation_matrix_x[2][1] = sin(angle_x);
	rotation_matrix_x[2][2] = cos(angle_x);
}

void	init_rotate_y(t_map *map, float rotation_matrix_y[3][3])
{
	float	angle_y;

	angle_y = RADIAN(map->rotate[Y]);
	init_matrix(rotation_matrix_y);
	rotation_matrix_y[0][0] = cos(angle_y);
	rotation_matrix_y[0][2] = sin(angle_y);
	rotation_matrix_y[1][1] = 1;
	rotation_matrix_y[2][0] = -sin(angle_y);
	rotation_matrix_y[2][2] = cos(angle_y);
}

void	init_rotate_z(t_map *map, float rotation_matrix_z[3][3])
{
	float	angle_z;

	angle_z = RADIAN(map->rotate[Z]);
	init_matrix(rotation_matrix_z);
	rotation_matrix_z[0][0] = cos(angle_z);
	rotation_matrix_z[0][1] = -sin(angle_z);
	rotation_matrix_z[1][0] = sin(angle_z);
	rotation_matrix_z[1][1] = cos(angle_z);
	rotation_matrix_z[2][2] = 1;
}

void	apply_transformations(t_map *map)
{
	float rotation_matrix_x[3][3];
	float rotation_matrix_y[3][3];
	float rotation_matrix_z[3][3];
	int	i;

	init_rotate_x(map, rotation_matrix_x);
	init_rotate_y(map, rotation_matrix_y);
	init_rotate_z(map, rotation_matrix_z);
	i = 0;
	while (i < map->size)
	{
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

	map->obj = (t_point *)malloc(sizeof(t_point) * map->size); //free obj before creating new one
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
			if (i % map->x_size < map->x_size -1)
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
			draw_dot(&data->img, map->obj[i]);
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
