/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:21:16 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/08 02:46:55 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	init_rotation_matrix(t_map *map)
{
	init_matrix(map->r_matrix.x);
	init_matrix(map->r_matrix.y);
	init_matrix(map->r_matrix.z);
}

void	init_image(t_mlx *data)
{
	data->img.ptr = mlx_new_image(data->mlx, WIN_W, WIN_H);
		data->img.buffer = mlx_get_data_addr(data->img.ptr,
			&data->img.pixel_bits, &data->img.line_bytes, &data->img.endian);
}

void	init_data(t_mlx *data)
{
	data->map.fd = 0;
	data->map.x_size = 0;
	data->map.y_size = 0;
	data->map.size = 0;
	data->map.zoom = 1;
	data->map.z_resize = 1;
	data->map.obj = NULL;
	data->map.mode = WIRE;
	data->map.t_render = 0;
	data->map.terrain = NULL;
	data->map.translate[X] = 0;
	data->map.translate[Y] = 0;
	data->key.axis_locked[X] = false;
	data->key.axis_locked[Y] = false;
	data->key.axis_locked[Z] = true;
	data->map.theme[BG_C] = GRAY_DARK;
	data->map.theme[OBJ1_C] = ORANGE;
	data->map.theme[OBJ2_C] = WHITE;
	data->map.theme[TEXT] = WHITE;
	data->map.col_axis[X] = COL_AXIS_X;
	data->map.col_axis[Y] = COL_AXIS_Y;
	data->map.col_axis[Z] = COL_AXIS_Z;
	data->img.ptr = NULL;
	data->key.first_left_click = true;
	data->key.first_right_click = true;
}

int	compare_str_end(char *str, char *end)
{
	int	len_str;
	int	len_end;

	len_str = ft_strlen(str);
	len_end = ft_strlen(end);
	return (ft_strcmp(str + len_str - len_end, end));
}

void	error_exit(char *mssg)
{
	ft_putstr_fd(mssg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
