/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:50:53 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/08 21:25:03 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	calculate_all_rotation_matrix(t_mlx *data)
{
	calculate_rotation_matrix(data->map.r_matrix.x, data->map.rotate[X], X);
	calculate_rotation_matrix(data->map.r_matrix.y, data->map.rotate[Y], Y);
	calculate_rotation_matrix(data->map.r_matrix.z, data->map.rotate[Z], Z);
}

void	mult_matrix(t_point *point, float (*matrix)[3])
{
	int		i;
	int		j;
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

void	calculate_rotation_matrix(float (*matrix)[3], float angle, uint8_t axis)
{
	if (axis == X)
	{
		matrix[0][0] = 1;
		matrix[1][1] = cos(angle * M_PI / 180);
		matrix[1][2] = -sin(angle * M_PI / 180);
		matrix[2][1] = sin(angle * M_PI / 180);
		matrix[2][2] = cos(angle * M_PI / 180);
	}
	else if (axis == Y)
	{
		matrix[0][0] = cos(angle * M_PI / 180);
		matrix[0][2] = sin(angle * M_PI / 180);
		matrix[1][1] = 1;
		matrix[2][0] = -sin(angle * M_PI / 180);
		matrix[2][2] = cos(angle * M_PI / 180);
	}
	else if (axis == Z)
	{
		matrix[0][0] = cos(angle * M_PI / 180);
		matrix[0][1] = -sin(angle * M_PI / 180);
		matrix[1][0] = sin(angle * M_PI / 180);
		matrix[1][1] = cos(angle * M_PI / 180);
		matrix[2][2] = 1;
	}
}
