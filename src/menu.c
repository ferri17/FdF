/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:23:46 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/06 21:41:04 by fbosch           ###   ########.fr       */
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
		my_string_put(data, WIN_W - (PAD * 2), PAD / 2, "error");
		return ;
	}
	render_t = ft_strjoin(time, " ms");
	if (!render_t)
	{
		free (time);
		my_string_put(data, WIN_W - (PAD * 2), PAD / 2, "error");
		return ;
	}
	my_string_put(data, WIN_W - (PAD * 2), PAD / 2, render_t);
	free (time);
	free (render_t);
}

static void	draw_axis_lock(t_mlx *data)
{
	if (data->key.axis_locked[Y] && data->key.axis_locked[Z])
		my_string_put(data, WIN_W - (PAD * 4), WIN_H - PAD, "AXIS X LOCKED");
	else if (data->key.axis_locked[X] && data->key.axis_locked[Z])
		my_string_put(data, WIN_W - (PAD * 4), WIN_H - PAD, "AXIS Y LOCKED");
	else if (data->key.axis_locked[X] && data->key.axis_locked[Y])
		my_string_put(data, WIN_W - (PAD * 4), WIN_H - PAD, "AXIS Z LOCKED");
	else
		my_string_put(data, WIN_W - (PAD * 4), WIN_H - PAD, "NO AXIS LOCKED");
}

/* void	draw_coordinates(t_mlx *data)
{
	char	*x;
	char	*y;

	my_string_put(data, MENU_W + PAD, WIN_H - PAD, "X:");
	my_string_put(data, MENU_W + PAD * 3, WIN_H - PAD, "Y:");
	x = ft_itoa(data->map.translate[X]);
	if (!x)
		my_string_put(data, MENU_W + PAD / 2 * 3, WIN_H - PAD, "???");
	else
		my_string_put(data, MENU_W + PAD / 2 * 3, WIN_H - PAD, x);
	y = ft_itoa(data->map.translate[Y]);
	if (!y)
		my_string_put(data, MENU_W + PAD / 2 * 7, WIN_H - PAD, "???");
	else
		my_string_put(data, MENU_W + PAD / 2 * 7, WIN_H - PAD, y);
	free(x);
	free(y);
} */

static void	draw_controls(t_mlx *data)
{
	my_string_put(data, PAD / 2, WIN_H - PAD * 9, "#####   CONTROLS   #####");
	my_string_put(data, PAD / 2, WIN_H - PAD * 7, "Move: Right click + drag");
	my_string_put(data, PAD / 2, WIN_H - PAD * 6, "Lock rotation: Hold X,Y,Z");
	my_string_put(data, PAD / 2, WIN_H - PAD * 5, "Theme color: 1,2,3");
	my_string_put(data, PAD / 2, WIN_H - PAD * 4, "Change height: N,M");
	my_string_put(data, PAD / 2, WIN_H - PAD * 3, "Line/dot mode: G");
	my_string_put(data, PAD / 2, WIN_H - PAD * 2, "Snap angle: Hold H");
	my_string_put(data, PAD / 2, WIN_H - PAD, "Change projection: I,P");
}

void	draw_menu(t_mlx *data)
{
	draw_controls(data);
	//draw_coordinates(data);
	draw_performance(data);
	draw_axis_lock(data);
}
