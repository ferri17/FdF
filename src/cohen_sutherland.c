/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cohen_sutherland.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:08:16 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/07 02:08:17 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

#define INSIDE 0
#define LEFT 1   // 0001
#define RIGHT 2  // 0010
#define BOTTOM 4 // 0100
#define TOP 8    // 1000
#define X_MIN 0
#define Y_MIN 0

static int	locate_region(int x, int y)
{
	int	code;

	code = INSIDE;
	if (x < X_MIN)
		code |= LEFT;
	else if (x > WIN_W2) // CHANGE
		code |= RIGHT;
	if (y < Y_MIN)
		code |= BOTTOM;
	else if (y > WIN_H2) // CHANGE
		code |= TOP;
	return (code);
}

static void	calculate_parallel_lines(int start[2], int end[2], t_cohen *data)
{
	if (start[Y] == end[Y] && (data->code_start & data->code_end))
	{
		if (data->code_start & LEFT)
			start[X] = X_MIN;
		else if (data->code_start & RIGHT)
			start[X] = WIN_W2;
		if (data->code_end & LEFT)
			end[X] = X_MIN;
		else if (data->code_end & RIGHT)
			end[X] = WIN_W2;
		data->accept = true;
	}
	if (start[X] == end[X] && (data->code_start & data->code_end))
	{
		if (data->code_start & BOTTOM)
			start[Y] = Y_MIN;
		else if (data->code_start & TOP)
			start[Y] = WIN_H2;
		if (data->code_end & BOTTOM)
			end[Y] = Y_MIN;
		else if (data->code_end & TOP)
			end[Y] = WIN_H2;
		data->accept = true;
	}
}

void	cohen_sutherland_clipping(int start[2], int end[2])
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
			calculate_parallel_lines(start, end, &data);
			if (data.code_start != 0)
				data.code_out = data.code_start;
			else
				data.code_out = data.code_end;
			if (data.code_out & TOP)
			{
				data.x = start[X] + (end[X] - start[X]) * (WIN_H2 - start[Y])
					/ (end[Y] - start[Y]);
				data.y = WIN_H2;
			}
			else if (data.code_out & BOTTOM)
			{
				data.x = start[X] + (end[X] - start[X]) * (Y_MIN - start[Y])
					/ (end[Y] - start[Y]);
				data.y = Y_MIN;
			}
			else if (data.code_out & RIGHT)
			{
				data.y = start[Y] + (end[Y] - start[Y]) * (WIN_W2 - start[X])
					/ (end[X] - start[X]);
				data.x = WIN_W2;
			}
			else if (data.code_out & LEFT)
			{
				data.y = start[Y] + (end[Y] - start[Y]) * (X_MIN - start[X])
					/ (end[X] - start[X]);
				data.x = X_MIN;
			}
			if (data.code_out == data.code_start)
			{
				start[X] = data.x;
				start[Y] = data.y;
				data.code_start = locate_region(start[X], start[Y]);
			}
			else
			{
				end[X] = data.x;
				end[Y] = data.y;
				data.code_end = locate_region(end[X], end[Y]);
			}
		}
	}
	if (!data.accept)
	{
		start[X] = 800;
		start[Y] = 800;
		end[X] = 800;
		end[Y] = 800;
	}
}
