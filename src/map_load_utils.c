/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:27:10 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/17 19:13:31 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void	get_heights(t_map *map)
{
	int		x;
	int		y;
	bool	zero;

	map->highest = INT_MIN;
	map->lowest = INT_MAX;
	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->y_size)
		{
			if (map->terrain[y][x].z > map->highest)
				map->highest = map->terrain[y][x].z;
			if (map->terrain[y][x].z < map->lowest)
				map->lowest = map->terrain[y][x].z;
			if (map->terrain[y][x].z == 0)
				zero = true;
			x++;
		}
		y++;
	}
	map->floor = map->lowest;
	if (zero)
		map->floor = 0;
	
}
