/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:47:06 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/05 11:06:11 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void	apply_transformations_circle(t_map *map, t_point *point,
		uint8_t axis)
{
	float	angle;
	float	x_matrix[3][3];

	if (axis == X || axis == Z)
	{
		if (axis == X)
			mult_matrix(point, map->r_matrix.x);
		mult_matrix(point, map->r_matrix.z);
		mult_matrix(point, map->r_matrix.y);
	}
	else if (axis == Y)
	{
		angle = 5;
		init_matrix(x_matrix);
		calculate_rotation_matrix(x_matrix, angle, X);
		mult_matrix(point, map->r_matrix.y);
		mult_matrix(point, x_matrix);
	}
	point->axis[X] += map->translate[X];
	point->axis[Y] += map->translate[Y];
}

static t_point	return_right_axis(int x, int y, uint8_t axis)
{
	t_point	aux;

	aux.axis[axis] = 0;
	if (axis == X)
	{
		aux.axis[Y] = y;
		aux.axis[Z] = x;
	}
	else if (axis == Y)
	{
		aux.axis[X] = y;
		aux.axis[Z] = x;
	}
	else if (axis == Z)
	{
		aux.axis[X] = x;
		aux.axis[Y] = y;
	}
	return (aux);
}

static bool	dotted_line(int *counter, int limit)
{
	(*counter)++;
	if (*counter > limit - 1)
		*counter = -limit;
	if (*counter >= 0)
		return (true);
	else
		return (false);
}

void	draw_rotation_axis(t_mlx *data, int radius, uint8_t axis)
{
	int		x;
	int		y;
	int		counter;
	t_point	aux;

	counter = 0;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (abs((x * x) + (y * y) - radius * radius) <= TOLERANCE)
			{
				aux = return_right_axis(x, y, axis);
				apply_transformations_circle(&data->map, &aux, axis);
				if (dotted_line(&counter, 20))
					my_put_pixel(data, aux.axis[X], aux.axis[Y],
						data->map.col_axis[axis]);
			}
			x++;
		}
		y++;
	}
}

void	draw_rotation_sphere(t_mlx *data, int radius)
{
	draw_rotation_axis(data, radius - 20, X);
	draw_rotation_axis(data, radius - 15, Z);
	draw_rotation_axis(data, radius, Y);
}
