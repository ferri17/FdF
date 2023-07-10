/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:08:24 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/11 00:43:03 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

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

void	fill_background(t_mlx *data, t_image *img, int color)
{
	if (!data)
		return;
	int	pixel;
	int	x;
	int	y;

	if (img->pixel_bits != 32)
   		color = mlx_get_color_value(data->mlx, color);
	y = 0;
	while(y < WIN_H)
	{
		x = 0;
		while(x < WIN_W)
		{
			pixel = (y * img->line_bytes) + (x * img->pixel_bits / 8);
			set_color(img, pixel, color);
			x++;
		}
		y++;
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

void	print_square(t_image *img, int size, int xo, int yo)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if ((i == 0 || i == size - 1|| j == 0 || j == size - 1))
				my_put_pixel(img, xo + j, yo + i, ACQUA);
		}
	}
}

void	print_line(t_image *img, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        my_put_pixel(img, x0, y0, WHITE);

        int err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }

    my_put_pixel(img, x1, y1, WHITE);
}

void	init_visualization(t_mlx *data, t_map *map)
{
	t_image	img;

	if (!map)
		return;
	img.ptr = mlx_new_image(data->mlx, WIN_W, WIN_H);
	img.buffer = mlx_get_data_addr(img.ptr, &img.pixel_bits, &img.line_bytes, &img.endian);
	fill_background(data, &img, BLACK);
	int	size = 900;
	print_square(&img, size, WIN_W/2 - size/2, WIN_H - 10 - size/2);
	print_line(&img, WIN_W/2, WIN_H/2, 0, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, img.ptr, 0, 0);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_mlx	data;

	if (ac != 2 || compare_str_end(av[1], ".fdf"))
		error_exit(USAGE);
	init_map(&map);
	load_map(av[1], &map);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_W, WIN_H, av[1]);
	init_visualization(&data, &map);
	mlx_key_hook(data.mlx_win, escape_key_hook, (void *)&data);
	mlx_hook(data.mlx_win, CROSS_EVENT, 0, close_program, (void *)&data);
	mlx_loop(data.mlx);
}

void	print_loaded_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size)
	{
		ft_printf("%i,%i,%i   ", map->terrain[i].pos[X], map->terrain[i].pos[Y],
			map->terrain[i].pos[Z]);
		if (map->terrain[i].pos[X] == map->x_size - 1)
			ft_printf("\n");
		i++;
	}
	ft_printf("\n");
	ft_printf("%i,%i,%i   ", map->terrain[i].pos[X], map->terrain[i].pos[Y],
		map->terrain[i].pos[Z]);
}
