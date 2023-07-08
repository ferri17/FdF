/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:08:24 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/08 11:50:28 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

void	init_visualization(t_mlx *data, t_map *map)
{
	t_image	img;

	if (map)
		img.ptr = mlx_new_image(data->mlx, WIN_W, WIN_H);
	img.buffer = mlx_get_data_addr(img.ptr, &img.pixel_bits, &img.line_bytes, &img.endian);
	ft_printf("Img ptr: %p\n", img.buffer);
	ft_printf("Img pixel bits: %i\n", img.pixel_bits);
	ft_printf("Img line bytes: %i\n", img.line_bytes);
	ft_printf("Img endian: %i\n", img.endian);
	ft_printf("Image: %s\n", img.buffer);
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
	data.mlx_win = mlx_new_window(data.mlx, WIN_W, WIN_H, "My first window");
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
