/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:23:46 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/23 12:05:13 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void	draw_performance(t_mlx *data)
{
	char	*time;
	char	*render_t;

	time = ft_itoa(data->map.t_render);
	if (!time)
	{
		mlx_string_put(data->mlx, data->mlx_win, WIN_W - (PAD * 2), PAD / 2, WHITE, "error");
		return ;
	}
	render_t = ft_strjoin(time, " ms");
	if (!render_t)
	{
		free (time);
		mlx_string_put(data->mlx, data->mlx_win, WIN_W - (PAD * 2), PAD / 2, WHITE, "error");
		return ;
	}
	mlx_string_put(data->mlx, data->mlx_win, WIN_W - (PAD * 2), PAD / 2, WHITE, render_t);
	free (time);
	free (render_t);
}

void	draw_axis_lock(t_mlx *data)
{
	if (data->key.axis_locked[Y] && data->key.axis_locked[Z])
		mlx_string_put(data->mlx, data->mlx_win, WIN_W - (PAD * 4), WIN_H - PAD, WHITE, "AXIS X LOCKED");
	else if (data->key.axis_locked[X] && data->key.axis_locked[Z])
		mlx_string_put(data->mlx, data->mlx_win, WIN_W - (PAD * 4), WIN_H - PAD, WHITE, "AXIS Y LOCKED");
	else if (data->key.axis_locked[X] && data->key.axis_locked[Y])
		mlx_string_put(data->mlx, data->mlx_win, WIN_W - (PAD * 4), WIN_H - PAD, WHITE, "AXIS Z LOCKED");
	else
		mlx_string_put(data->mlx, data->mlx_win, WIN_W - (PAD * 4), WIN_H - PAD, WHITE, "NO AXIS LOCKED");
}

void	draw_rotation(t_mlx *data)
{
	//mlx_string_put(data->mlx, data->mlx_win, PAD / 2, PAD, WHITE, "X, Y, Z: ");
	//mlx_string_put(data->mlx, data->mlx_win, PAD * 3, PAD, WHITE, ft_itoa(data->map.rotate[X]));
	//mlx_string_put(data->mlx, data->mlx_win, PAD * 4, PAD, WHITE, ft_itoa(data->map.rotate[Y]));
	//mlx_string_put(data->mlx, data->mlx_win, PAD * 5, PAD, WHITE, ft_itoa(data->map.rotate[Z]));

}

void	draw_menu(t_mlx *data)
{
	draw_rotation(data);
	draw_performance(data);
	draw_axis_lock(data);
}