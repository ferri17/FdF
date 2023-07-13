/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:39:23 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/13 14:44:02 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

int	key_hook(int keycode, void *param)
{
	if (keycode == ESC_KEY)
		close_program(param, EXIT_SUCCESS);
	if (keycode == PLUS_KEY)
		zoom_in(param);
	if (keycode == MINUS_KEY)
		zoom_out(param);
/* 	if (keycode == O_KEY)
		height_down(param);
	if (keycode == P_KEY)
		height_up(param); */
	return (0);
}
/* void	height_up(void *param)
{
	t_mlx	*data;
	void	*aux_img;

	data = (t_mlx *)param;
	iterate_terrain(data->map.terrain, );
	aux_img = data->img.ptr;
	init_visualization(data, &data->map);
	mlx_destroy_image(data->mlx, aux_img);
} */

void	zoom_in(void *param)
{
	t_mlx	*data;
	void	*aux_img;

	data = (t_mlx *)param;
	data->map.zoom *= 1.25;
	aux_img = data->img.ptr;
	init_visualization(data, &data->map);
	mlx_destroy_image(data->mlx, aux_img);
}

void	zoom_out(void *param)
{
	t_mlx	*data;
	void	*aux_img;

	data = (t_mlx *)param;
	data->map.zoom /= 1.25;
	aux_img = data->img.ptr;
	init_visualization(data, &data->map);
	mlx_destroy_image(data->mlx, aux_img);
}

int	close_program(void *param, int exit_code)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy(data->mlx);
	exit(exit_code);
}
