/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:08:24 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/12 00:48:48 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

void	draw_map(t_map *map, t_image *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
		{
			if (x != map->x_size -1)
				print_line(img, x, y, x + 1, y);
			if (y != map->y_size -1)
				print_line(img, x, y, x, y + 1);
			x++;
		}
		y++;
	}
}

void	init_visualization(t_mlx *data, t_map *map)
{
	t_image	img;

	if (!map)
		return;
	img.ptr = mlx_new_image(data->mlx, WIN_W, WIN_H);
	img.buffer = mlx_get_data_addr(img.ptr, &img.pixel_bits, &img.line_bytes, &img.endian);
	fill_background(data, &img, BLACK);
	draw_map(map, &img);
	//print_line(&img, WIN_W/2, WIN_H/2, 0, 0);
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
