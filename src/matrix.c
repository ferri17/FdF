/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:50:53 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/23 12:13:08 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

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
			point->axis[i] += temp[j] * matrix[i][j];
			j++;
		}
		i++;
	}
}

void	init_matrix(float matrix[3][3])
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
