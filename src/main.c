/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:08:24 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/22 03:57:00 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	init_visualization(t_mlx *data)
{
	void	*aux_ptr;
	t_point	*temp_obj;
	clock_t	t;

	t = clock();
	aux_ptr = NULL;
	temp_obj = NULL;
	if (data->img.ptr != NULL)
		aux_ptr = data->img.ptr;
	if (data->map.obj != NULL)
		temp_obj = data->map.obj;
	init_image(data);
	fill_background(data, data->map.theme[BG_C]);
	draw_map(data, &data->map);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.ptr, 0, 0);
	if (aux_ptr != NULL)
		mlx_destroy_image(data->mlx, aux_ptr);
	free(temp_obj);
	t = clock() - t;
	data->map.t_render = ((double)t) / CLOCKS_PER_SEC * 1000;
	draw_menu(data);
}

int	main(int ac, char **av)
{
	t_mlx	data;

	if (ac != 2 || compare_str_end(av[1], ".fdf"))
		error_exit(USAGE);
	init_data(&data);
	load_map(av[1], &data.map);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_W, WIN_H, av[1]);
	init_visualization(&data);
	mlx_hook(data.mlx_win, KEYDOWN, 0, key_down, (void *)&data);
	mlx_hook(data.mlx_win, MOUSEDOWN, 0, mouse_down, (void *)&data);
	mlx_hook(data.mlx_win, MOUSEUP, 0, mouse_up, (void *)&data);
	mlx_hook(data.mlx_win, MOUSEMOVE, 0, mouse_move, (void *)&data);
	mlx_hook(data.mlx_win, DESTROY, 0, close_program, (void *)&data);
	mlx_loop(data.mlx);
}
