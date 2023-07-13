/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:03:56 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/13 01:25:36 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

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
			map->x0 = x;
			map->y0 = y;
			map->x1 = x;
			map->y1 = y;
			if (x != map->x_size -1)
			{
				map->x1 += 1;
				bresenham(map, &data->img);
			}
			map->x1 = x;
			if (y != map->y_size -1)
			{
				map->y1 += 1;
				bresenham(map, &data->img);			
			}
			//ft_printf("X0, Y0: %i, %i ----- X1, Y1: %i, %i\n", map->line[X0], map->line[Y0], map->line[X1], map->line[Y1]);
			x++;
		}
		y++;
	}
}

void	fill_background(t_mlx *data, int color)
{
	int	x;
	int	y;

	if (data->img.pixel_bits != 32)
   		color = mlx_get_color_value(data->mlx, color);
	y = 0;
	while(y < WIN_H)
	{
		x = 0;
		while(x < WIN_W)
		{
			my_put_pixel(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	set_color(t_image *img, int pixel, int color)
{
	if (img->endian == 1)        // Most significant (Alpha) byte first
    {
        img->buffer[pixel + 0] = (color >> 24);
        img->buffer[pixel + 1] = (color >> 16) & 0xFF;
        img->buffer[pixel + 2] = (color >> 8) & 0xFF;
        img->buffer[pixel + 3] = (color) & 0xFF;
    }
    else if (img->endian == 0)   // Least significant (Blue) byte first
    {
        img->buffer[pixel + 0] = (color) & 0xFF;
        img->buffer[pixel + 1] = (color >> 8) & 0xFF;
        img->buffer[pixel + 2] = (color >> 16) & 0xFF;
        img->buffer[pixel + 3] = (color >> 24);
    }
}

int	my_put_pixel(t_image *img, int x, int y, int color)
{
	int	pixel;

	if(x >= WIN_W || y >= WIN_H)
		return (1);
	pixel = (img->line_bytes * y) + (x * img->pixel_bits / 8);
	set_color(img, pixel, color);
	return (0);
}

void	print_loaded_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
		{
			ft_printf("%i,%i,%i   ", x, y, map->terrain[y][x].z);
			x++;
		}
		ft_printf("\n");
		y++;
	}
	ft_printf("\n");
}
