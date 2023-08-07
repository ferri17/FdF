/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:50:09 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/08 03:05:50 by fbosch           ###   ########.fr       */
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

static t_bresenh	init_bresenham_variables(t_mlx *data, t_line *line)
{
	t_bresenh	info;

	info.accept = cohen_sutherland_clipping(line->start.axis, line->end.axis);
	info.draw.start[X] = (int)round(line->start.axis[X]);
	info.draw.start[Y] = (int)round(line->start.axis[Y]);
	info.draw.end[X] = (int)round(line->end.axis[X]);
	info.draw.end[Y] = (int)round(line->end.axis[Y]);
	info.dx = abs(info.draw.end[X] - info.draw.start[X]);
	info.dy = abs(info.draw.end[Y] - info.draw.start[Y]);
	info.sx = find_biggest(info.draw.start[X], info.draw.end[X]);
	info.sy = find_biggest(info.draw.start[Y], info.draw.end[Y]);
	info.err = info.dx - info.dy;
	return (info);
}

static void	decide_error_bresenham(t_bresenh *info, int *i)
{
	info->err2 = 2 * info->err;
	if (info->err2 > -info->dy)
	{
		info->err -= info->dy;
		info->draw.start[X] += info->sx;
	}
	if (info->err2 < info->dx)
	{
		(*i)++;
		info->err += info->dx;
		info->draw.start[Y] += info->sy;
	}
}

void	bresenham(t_mlx *data, t_line line)
{
	t_bresenh	info;
	int			col;
	int			i;

	i = 0;
	info = init_bresenham_variables(data, &line);
	if (!info.accept)
		return ;
	while (info.draw.start[X] != info.draw.end[X]
		|| info.draw.start[Y] != info.draw.end[Y])
	{
		col = get_color_gradient(line.start.color, line.end.color, info.dy, i);
		my_put_pixel(data, info.draw.start[X], info.draw.start[Y], col);
		decide_error_bresenham(&info, &i);
	}
	my_put_pixel(data, info.draw.end[X], info.draw.end[Y], col);
}
