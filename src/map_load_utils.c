/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:27:10 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/08 21:24:54 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	calculate_start_position(t_mlx *data)
{
	data->map.translate[X] = WIN_W / 2 + PAD * 2;
	data->map.translate[Y] = WIN_H / 2 + PAD;
	data->map.zoom *= ((WIN_W / 2) / data->map.x_size) + 1;
	data->map.rotate[X] = 63;
	data->map.rotate[Y] = -39;
	data->map.rotate[Z] = 24;
}

static void	get_heights(t_map *map)
{
	int		i;

	map->highest = INT_MIN;
	map->lowest = INT_MAX;
	i = 0;
	while (i < map->size)
	{
		if (map->terrain[i].axis[Z] > map->highest)
			map->highest = map->terrain[i].axis[Z];
		if (map->terrain[i].axis[Z] < map->lowest)
			map->lowest = map->terrain[i].axis[Z];
		i++;
	}
}

void	map_colors(t_map *map)
{
	int	len;
	int	pro;
	int	i;

	get_heights(map);
	len = map->highest - map->lowest;
	i = 0;
	while (i < map->size)
	{
			pro = map->terrain[i].axis[Z] - map->lowest;
			map->terrain[i].color = get_color_gradient(map->theme[OBJ1_C], \
				map->theme[OBJ2_C], len, pro);
			i++;
	}
}
