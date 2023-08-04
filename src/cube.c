/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:52:40 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/04 21:25:15 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void	set_color_cube(t_mlx *data, t_point *cube)
{
	int	i;

	i = 0;
	while (i < CUBE_VERTEX)
	{
		cube[i].color = data->map.theme[TEXT];
		i++;
	}
}

static void	init_cube(t_mlx *data, t_point *cube)
{
	set_color_cube(data, cube);
	cube[0].axis[X] = -30;
	cube[0].axis[Y] = -30;
	cube[0].axis[Z] = 30;
	cube[1].axis[X] = 30;
	cube[1].axis[Y] = -30;
	cube[1].axis[Z] = 30;
	cube[2].axis[X] = 30;
	cube[2].axis[Y] = 30;
	cube[2].axis[Z] = 30;
	cube[3].axis[X] = -30;
	cube[3].axis[Y] = 30;
	cube[3].axis[Z] = 30;
	cube[4].axis[X] = -30;
	cube[4].axis[Y] = -30;
	cube[4].axis[Z] = -30;
	cube[5].axis[X] = 30;
	cube[5].axis[Y] = -30;
	cube[5].axis[Z] = -30;
	cube[6].axis[X] = 30;
	cube[6].axis[Y] = 30;
	cube[6].axis[Z] = -30;
	cube[7].axis[X] = -30;
	cube[7].axis[Y] = 30;
	cube[7].axis[Z] = -30;
}

static void	apply_transformations_cube(t_map *map, t_point cube[CUBE_VERTEX])
{
	int		i;

	i = 0;
	while (i < CUBE_VERTEX)
	{
		mult_matrix(&cube[i], map->r_matrix.x);
		mult_matrix(&cube[i], map->r_matrix.z);
		mult_matrix(&cube[i], map->r_matrix.y);
		cube[i].axis[X] += PAD * 3 / 2;
		cube[i].axis[Y] += PAD * 3 / 2;
		i++;
	}
}

static void	draw_axis(t_mlx *data, t_point *cube)
{
	t_line	line;

	line.start = cube[0];
	line.end = cube[4];
	line.start.color = data->map.col_axis[Z];
	line.end.color = data->map.col_axis[Z];
	bresenham(data, line);
	line.start = cube[4];
	line.end = cube[5];
	line.start.color = data->map.col_axis[X];
	line.end.color = data->map.col_axis[X];
	bresenham(data, line);
	line.start = cube[4];
	line.end = cube[7];
	line.start.color = data->map.col_axis[Y];
	line.end.color = data->map.col_axis[Y];
	bresenham(data, line);
}

void 	draw_cube(t_mlx *data)
{
	t_point	cube[CUBE_VERTEX];
	t_line	line;
	int	i;

	init_cube(data, cube);
	apply_transformations_cube(&data->map, cube);
	i = 0;
	while (i < CUBE_VERTEX)
	{
		if (i == 0 || i == 2 || i == 4 || i == 6)
		{
			line.start = cube[i];
			line.end = cube[i + 1];
			bresenham(data, line);
			if (i == 0 || i == 4)
			{
				line.start = cube[i];
				line.end = cube[i + 3];
			}
			else
			{
				line.start = cube[i];
				line.end = cube[i - 1];
			}
			bresenham(data, line);
		}
		if (i == 0 || i == 1 || i == 2 || i == 3)
		{
			line.start = cube[i];
			line.end = cube[i + 4];
			bresenham(data, line);
		}
		i++;
	}
	draw_axis(data, cube);
}