/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:50:09 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/20 16:58:51 by fbosch           ###   ########.fr       */
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

	info.draw.start[X] = (int)round(line->start.axis[X]);
	info.draw.start[Y] = (int)round(line->start.axis[Y]);
	info.draw.end[X] = (int)round(line->end.axis[X]);
	info.draw.end[Y] = (int)round(line->end.axis[Y]);
	info.dx = abs(info.draw.end[X] - info.draw.start[X]);
	info.dy = abs(info.draw.end[Y] - info.draw.start[Y]);
	info.sx = find_biggest(info.draw.start[X], info.draw.end[X]);
	info.sy = find_biggest(info.draw.start[Y], line->end.axis[Y]);
	info.err = info.dx - info.dy;
	return (info);
}

void	bresenham(t_mlx *data, t_line line, int color0, int color1)
{
	t_bresenh	info;
	int			color;
	int			k;

	info = init_bresenham_variables(data, &line);
	while (info.draw.start[X] != info.draw.end[X] || info.draw.start[Y] != info.draw.end[Y])
	{
		//ft_printf("dx %i\ndy %i\nsx %i\nsy %i\nerr %i\nerr2 %i\n", info.dx, info.dy, info.sx, info.sy, info.err, info.err2);
		//ft_printf("%i,%i      ->    %i,%i\n", (int)line.start.axis[X], (int)line.start.axis[Y], (int)line.end.axis[X], (int)line.end.axis[Y]);
		color = get_color_gradient(color0, color1, info.dy, k);
		my_put_pixel(&data->img, info.draw.start[X], info.draw.start[Y], WHITE);
		info.err2 = 2 * info.err;
		if (info.err2 > -info.dy)
		{
			info.err -= info.dy;
			info.draw.start[X] += info.sx;
		}
		if (info.err2 < info.dx)
		{
			k++;
			info.err += info.dx;
			info.draw.start[Y] += info.sy;
		}
	}
	//ft_printf("%i,%i      ->    %i,%i\n", (int)line.start.axis[X], (int)line.start.axis[Y], (int)line.end.axis[X], (int)line.end.axis[Y]);
	//ft_printf("\n\n");
	my_put_pixel(&data->img, info.draw.end[X], info.draw.end[Y], WHITE);
		// CHECK IF ITS NEDEED OR IT CREATES DOUBLE LINES
}
