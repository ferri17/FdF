/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:50:09 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/13 02:31:03 by fbosch           ###   ########.fr       */
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

static void	get_zoom(t_bresenh *info, t_map *map)
{
	info->start[X] *= map->zoom;
	info->start[Y] *= map->zoom;
	info->end[X] *= map->zoom;
	info->end[Y] *= map->zoom;
}

void	isometric(int *x, int *y, int z)
{
	int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = (previous_x + previous_y) * sin(0.523599) - z;
}
static t_bresenh	init_bresenham_variables(t_map *map)
{
	t_bresenh	info;

	int x0 = info.start[X] = map->x0;
	int y0 = info.start[Y] = map->y0;
	int x1 = info.end[X] = map->x1;
	int y1 = info.end[Y] = map->y1;
	ft_printf("start: %i, %i      end: %i, %i\n", info.start[X], info.start[Y], info.end[X], info.end[Y]);
	get_zoom(&info, map);
	ft_printf("start: %i, %i      end: %i, %i\n", info.start[X], info.start[Y], info.end[X], info.end[Y]);
	ft_printf("start: %i, %i      end: %i, %i\n", info.start[X], info.start[Y], info.end[X], info.end[Y]);
	isometric(&info.start[X], &info.start[Y], map->terrain[y0][x0].z);
	isometric(&info.end[X], &info.end[Y], map->terrain[y1][x1].z);
	info.dx = abs(info.end[X] - info.start[X]);
    info.dy = abs(info.end[Y] - info.start[Y]);
	info.sx = find_biggest(info.start[X], info.end[X]);
	info.sy = find_biggest(info.start[Y], info.end[Y]);
    info.err = info.dx - info.dy;
	return (info);
}

void	bresenham(t_map *map, t_image *img)
{
	t_bresenh	info;
	
	info = init_bresenham_variables(map);
    while (info.start[X] != info.end[X] || info.start[Y] != info.end[Y]) 
	{
		ft_printf("start: %i, %i      end: %i, %i\n", info.start[X], info.start[Y], info.end[X], info.end[Y]);
        my_put_pixel(img, info.start[X], info.start[Y], BLACK);
        info.err2 = 2 * info.err;
        if (info.err2 > -info.dy) 
		{
            info.err -= info.dy;
            info.start[X] += info.sx;
        }
        if (info.err2 < info.dx) 
		{
            info.err += info.dx;
            info.start[Y] += info.sy;
        }
    }
	my_put_pixel(img, info.end[X], info.end[Y], BLACK);
}
