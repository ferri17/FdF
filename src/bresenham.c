/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:50:09 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/14 19:19:46 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

static int	find_biggest(int n1, int n2)
{
	if (n1 < n2)
		return (1);
	return (-1);
}

static void	get_zoom(t_line *line, t_mlx *data, int *z0, int *z1)
{
	line->x0 *= data->map.zoom;
	line->y0 *= data->map.zoom;
	line->x1 *= data->map.zoom;
	line->y1 *= data->map.zoom;
	*z0 *= data->map.zoom;
	*z1 *= data->map.zoom;
}

void	isometric(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = (previous_x + previous_y) * sin(0.523599) - z;
}

static t_bresenh	init_bresenham_variables(t_mlx *data, t_line *line)
{
	t_bresenh	info;
	int			z0;
	int			z1;

	z0 = data->map.terrain[line->y0][line->x0].z;
	z1 = data->map.terrain[line->y1][line->x1].z;
	get_zoom(line, data, &z0, &z1);
	isometric(&line->x0, &line->y0, z0);
	isometric(&line->x1, &line->y1, z1);
	info.dx = abs(line->x1 - line->x0);
	info.dy = abs(line->y1 - line->y0);
	info.sx = find_biggest(line->x0, line->x1);
	info.sy = find_biggest(line->y0, line->y1);
	info.err = info.dx - info.dy;
	return (info);
}

void	bresenham(t_mlx *data, t_line line)
{
	t_bresenh	info;

	info = init_bresenham_variables(data, &line);
	while ((line.x0 != line.x1 || line.y0 != line.y1))
	{
		my_put_pixel(&data->img, line.x0 + 400, line.y0 + 200, BLACK);
		info.err2 = 2 * info.err;
		if (info.err2 > -info.dy)
		{
			info.err -= info.dy;
			line.x0 += info.sx;
		}
		if (info.err2 < info.dx)
		{
			info.err += info.dx;
			line.y0 += info.sy;
		}
	}
	my_put_pixel(&data->img, line.x1 + 400, line.y1 + 200, BLACK);
		// CHECK IF ITS NEDEED OR IT CREATES DOUBLE LINES
}
