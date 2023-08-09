/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:46:50 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/08 21:24:40 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	rotate_object(t_mlx *data, int key)
{
	if (key == I_KEY)
	{
		data->map.rotate[X] = 63;
		data->map.rotate[Y] = -39;
		data->map.rotate[Z] = 24;
	}
	if (key == P_KEY)
	{
		data->map.rotate[X] = 90;
		data->map.rotate[Y] = 0;
		data->map.rotate[Z] = 0;
	}
	init_visualization(data);
}

void	move_map(t_mlx *data, int key)
{
	if (key == A_KEY)
		data->map.translate[X] -= TRANSL;
	if (key == S_KEY)
		data->map.translate[Y] += TRANSL;
	if (key == D_KEY)
		data->map.translate[X] += TRANSL;
	if (key == W_KEY)
		data->map.translate[Y] -= TRANSL;
	init_visualization(data);
}

void	change_height(t_mlx *data, int key)
{
	float	height;

	if (key == M_KEY)
		height = HEIGHT_UP;
	else
		height = HEIGHT_DOWN;
	data->map.z_resize *= height;
	init_visualization(data);
}

int	close_program(t_mlx *data, int exit_code)
{
	mlx_destroy_image(data->mlx, data->img.ptr);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy(data->mlx);
	free(data->map.terrain);
	free(data->map.obj);
	exit(exit_code);
}

void	change_mode(t_mlx *data)
{
	data->map.mode = ((data->map.mode + 1) % 2) + 30;
	init_visualization(data);
}
