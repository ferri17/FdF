/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:50:09 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/30 23:47:09 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static int	find_biggest(float n1, float n2)
{
	if (n1 < n2)
		return (1);
	return (-1);
}

static void	optimize_long_lines(t_bresenh *info)
{
	float	m;
	int		b;
	int		inter[4][2];
	int		is_out;

	is_out = 0;
	if ((info->draw.start[X] < 0 || info->draw.start[X] > WIN_W
			|| info->draw.start[Y] < 0 || info->draw.start[Y] > WIN_H)
		&& (info->draw.end[X] < 0 || info->draw.end[X] > WIN_W
			|| info->draw.end[Y] < 0 || info->draw.end[Y] > WIN_H))
	{
		if (info->draw.end[X] - info->draw.start[X] == 0)
		{
			if (info->draw.start[X] < 0 || info->draw.start[X] > WIN_W)
			{
				info->draw.start[X] = -1;
				info->draw.start[Y] = -1;
				info->draw.end[X] = -1;
				info->draw.end[Y] = -1;
			}
		}
		else if (info->draw.end[Y] - info->draw.start[Y] == 0)
		{
			if (info->draw.start[Y] < 0 || info->draw.start[Y] > WIN_H)
			{
				info->draw.start[X] = -1;
				info->draw.start[Y] = -1;
				info->draw.end[X] = -1;
				info->draw.end[Y] = -1;
			}
		}
		else
		{
			m = (info->draw.end[Y] - info->draw.start[Y]) / (info->draw.end[X]
				- info->draw.start[X]);
			b = info->draw.start[Y] - (m * info->draw.start[X]);
			inter[0][X] = (WIN_H - b) / m; // CHECKS HORIZONTAL MAX Y = WIN_H
			inter[0][Y] = WIN_H;
			inter[1][X] = 0; // CHECKS VERTICAL MIN X = 0
			inter[1][Y] = b;
			inter[2][X] = -b / m; // CHECKS HORIZONTAL MIN Y = 0
			inter[2][Y] = 0;
			inter[3][X] = WIN_W; // CHECKS VERTICAL MAX X = WIN_W
			inter[3][Y] = (m * WIN_W) + b;
			if (inter[0][X] < 0 || inter[0][X] > WIN_W)
				is_out++;
			if (inter[2][X] < 0 || inter[2][X] > WIN_W)
				is_out++;
			if (inter[1][Y] < 0 || inter[1][Y] > WIN_H)
				is_out++;
			if (inter[3][Y] < 0 || inter[3][Y] > WIN_H)
				is_out++;
			if (is_out == 4)
			{
				info->draw.start[X] = -1;
				info->draw.start[Y] = -1;
				info->draw.end[X] = -1;
				info->draw.end[Y] = -1;
			}
		}
	}
}

static t_bresenh	init_bresenham_variables(t_mlx *data, t_line *line)
{
	t_bresenh	info;

	info.draw.start[X] = (int)round(line->start.axis[X]);
	info.draw.start[Y] = (int)round(line->start.axis[Y]);
	info.draw.end[X] = (int)round(line->end.axis[X]);
	info.draw.end[Y] = (int)round(line->end.axis[Y]);
	optimize_long_lines(&info);
	info.dx = abs(info.draw.end[X] - info.draw.start[X]);
	info.dy = abs(info.draw.end[Y] - info.draw.start[Y]);
	info.sx = find_biggest(info.draw.start[X], info.draw.end[X]);
	info.sy = find_biggest(info.draw.start[Y], info.draw.end[Y]);
	info.err = info.dx - info.dy;
	return (info);
}

void	bresenham(t_mlx *data, t_line line)
{
	t_bresenh	info;
	int			col;
	int			i;

	i = 0;
	info = init_bresenham_variables(data, &line);
	while (info.draw.start[X] != info.draw.end[X]
		|| info.draw.start[Y] != info.draw.end[Y])
	{
		col = get_color_gradient(line.start.color, line.end.color, info.dy, i);
		my_put_pixel(data, info.draw.start[X], info.draw.start[Y], col);
		info.err2 = 2 * info.err;
		if (info.err2 > -info.dy)
		{
			info.err -= info.dy;
			info.draw.start[X] += info.sx;
		}
		if (info.err2 < info.dx)
		{
			i++;
			info.err += info.dx;
			info.draw.start[Y] += info.sy;
		}
	}
	my_put_pixel(data, info.draw.end[X], info.draw.end[Y], col);
}
