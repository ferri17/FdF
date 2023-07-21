/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:46:50 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/21 21:17:05 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	rotate_object(void *param, int key)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (key == X_KEY)
		data->map.rotate[X] += MY_ROTATION;
	else if (key == Y_KEY)
		data->map.rotate[Y] += MY_ROTATION;
	else if (key == Z_KEY)
		data->map.rotate[Z] += MY_ROTATION;
	init_visualization(data, &data->map);
}

void	move_map(void *param, int key)
{
	t_mlx *data;

	data = (t_mlx *)param;
	if (key == A_KEY)
		data->map.translate[X] -= TRANSL;
	if (key == S_KEY)
		data->map.translate[Y] += TRANSL;
	if (key == D_KEY)
		data->map.translate[X] += TRANSL;
	if (key == W_KEY)
		data->map.translate[Y] -= TRANSL;
	init_visualization(data, &data->map);
}

void	iterate_terrain(t_map *map, int delta)
{
	int		x;
	int		y;
	float	mult;

	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
		{
			//if (map->terrain[y][x].z != map->floor)
			//	map->terrain[y][x].z += delta;
			x++;
		}
		y++;
	}
}

void	change_height(void *param, int delta)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	//iterate_terrain(&data->map, delta);
	//init_visualization(data, &data->map);
}

void	zoom_screen(void *param, float zoom)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	data->map.zoom *= zoom;
	init_visualization(data, &data->map);
}

int	close_program(void *param, int exit_code)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	mlx_destroy_image(data->mlx, data->img.ptr);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy(data->mlx);
	free(data->map.terrain);
	exit(exit_code);
}
