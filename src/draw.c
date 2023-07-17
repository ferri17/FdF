/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:03:56 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/17 02:28:15 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	draw_map(t_mlx *data, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
		{
			//ft_printf("aa\n");
			ft_printf("colors-> 0x%x\n", map->terrain[y][x].color);
			map->line.x0 = x;
			map->line.y0 = y;
			map->line.x1 = x + 1;
			map->line.y1 = y;
			if (x != map->x_size - 1)
				bresenham(data, data->map.line, x, y, x + 1, y);
			map->line.x1 = x;
			map->line.y1 = y + 1;
			if (y != map->y_size - 1)
				bresenham(data, data->map.line, x, y, x, y + 1);
			x++;
		}
		y++;
	}
}

void	fill_background(t_mlx *data, int color1, int color2)
{
	int	x;
	int	y;
	int	k;
	int	color;
	
	if (data->img.pixel_bits != 32)
	{
		color1 = mlx_get_color_value(data->mlx, color1);
		color2 = mlx_get_color_value(data->mlx, color2);
	}
	k = 0;
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			color = get_color_gradient(color1, color2, WIN_W * WIN_H, k);
			my_put_pixel(&data->img, x, y, color);
			x++;
			k++;
		}
		y++;
	}
}

int	my_put_pixel(t_image *img, int x, int y, int color)
{
	int	pixel;

	if (x >= WIN_W || y >= WIN_H || x < 0 || y < 0)
		return (1);
	pixel = (img->line_bytes * y) + (x * img->pixel_bits / 8);
	set_color(img, pixel, color);
	return (0);
}
