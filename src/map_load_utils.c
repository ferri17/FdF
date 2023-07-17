/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:27:10 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/17 01:30:10 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

int	get_highest(t_map *map)
{
	int	highest;
	int	x;
	int	y;

	highest = INT_MIN;
	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->y_size)
		{
			if (map->terrain[y][x].z > highest)
				highest = map->terrain[y][x].z;
			x++;
		}
		y++;
	}
	return (highest);
}

int	get_lowest(t_map *map)
{
	int	lowest;
	int	x;
	int	y;

	lowest = INT_MAX;
	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->y_size)
		{
			if (map->terrain[y][x].z < lowest)
				lowest = map->terrain[y][x].z;
			x++;
		}
		y++;
	}
	return (lowest);
}