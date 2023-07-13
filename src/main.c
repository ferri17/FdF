/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:08:24 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/13 13:37:28 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

void	init_visualization(t_mlx *data, t_map *map)
{
	//print_loaded_map(map);
	data->img.ptr = mlx_new_image(data->mlx, WIN_W, WIN_H);
	data->img.buffer = mlx_get_data_addr(data->img.ptr, &data->img.pixel_bits,\
			&data->img.line_bytes, &data->img.endian);
	fill_background(data, WHITE);
	draw_map(data, map);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
}

int	main(int ac, char **av)
{
	t_mlx	data;

	if (ac != 2 || compare_str_end(av[1], ".fdf"))
		error_exit(USAGE);
	init_map(&data.map);
	load_map(av[1], &data.map);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_W, WIN_H, av[1]);
	init_visualization(&data, &data.map);
	mlx_key_hook(data.mlx_win, key_hook, (void *)&data);
	mlx_hook(data.mlx_win, CROSS_EVENT, 0, close_program, (void *)&data);
	mlx_loop(data.mlx);
}
