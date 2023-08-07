/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cohen_sutherland.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:08:16 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/08 00:58:21 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8
#define X_MIN 0
#define Y_MIN 0

static int	locate_region(float x, float y)
{
	int	code;

	code = INSIDE;
	if (x < X_MIN)
		code |= LEFT;
	else if (x > WIN_W)
		code |= RIGHT;
	if (y < Y_MIN)
		code |= BOTTOM;
	else if (y > WIN_H)
		code |= TOP;
	return (code);
}

static void	locate_intersec_point(t_cohen *data, float start[3], float end[3])
{
	if (data->code_out & TOP)
	{
		data->x = start[X] + (end[X] - start[X]) * (WIN_H - start[Y])
			/ (end[Y] - start[Y]);
		data->y = WIN_H;
	}
	else if (data->code_out & BOTTOM)
	{
		data->x = start[X] + (end[X] - start[X]) * (Y_MIN - start[Y])
			/ (end[Y] - start[Y]);
		data->y = Y_MIN;
	}
	else if (data->code_out & RIGHT)
	{
		data->y = start[Y] + (end[Y] - start[Y]) * (WIN_W - start[X])
			/ (end[X] - start[X]);
		data->x = WIN_W;
	}
	else if (data->code_out & LEFT)
	{
		data->y = start[Y] + (end[Y] - start[Y]) * (X_MIN - start[X])
			/ (end[X] - start[X]);
		data->x = X_MIN;
	}
}

static void	update_new_point(t_cohen *data, float start[3], float end[3])
{
	if (data->code_out == data->code_start)
	{
		start[X] = data->x;
		start[Y] = data->y;
		data->code_start = locate_region(start[X], start[Y]);
	}
	else
	{
		end[X] = data->x;
		end[Y] = data->y;
		data->code_end = locate_region(end[X], end[Y]);
	}
}

bool	cohen_sutherland_clipping(float start[3], float end[3])
{
	t_cohen	data;

	data.code_start = locate_region(start[X], start[Y]);
	data.code_end = locate_region(end[X], end[Y]);
	data.accept = false;
	while (!data.accept)
	{
		if ((data.code_start == 0) && (data.code_end == 0))
			data.accept = true;
		else if (data.code_start & data.code_end)
			break ;
		else
		{
			if (data.code_start != 0)
				data.code_out = data.code_start;
			else
				data.code_out = data.code_end;
			locate_intersec_point(&data, start, end);
			update_new_point(&data, start, end);
		}
	}
	return (data.accept);
}
