/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:21:16 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/14 19:17:58 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

void	init_data(t_mlx *data)
{
	data->map.fd = 0;
	data->map.x_size = 0;
	data->map.y_size = 0;
	data->map.size = 0;
	data->map.zoom = 20;
	data->map.terrain = NULL;
	data->img.ptr = NULL;
	data->map.translate[X] = 0;
	data->map.translate[Y] = 0;
}

void	free_terrain(t_map *map, int i)
{
	while (i >= 0)
	{
		free(map->terrain[i]);
		i--;
	}
	free(map->terrain);
}

int	compare_str_end(char *str, char *end)
{
	int	len_str;
	int	len_end;

	len_str = ft_strlen(str);
	len_end = ft_strlen(end);
	return (ft_strcmp(str + len_str - len_end, end));
}

void	free_and_close(t_mlx *data, t_map *map, t_image *img, int exit_code)
{
	mlx_destroy_image(data->mlx, img->ptr);
	free(map->terrain);
	if (exit_code != EXIT_SUCCESS)
		ft_putstr_fd(UNEXPECTED_ERR, 2);
	close_program(data, exit_code);
}
