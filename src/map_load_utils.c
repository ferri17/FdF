/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:27:10 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/20 15:38:16 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void	get_heights(t_map *map)
{
	int		i;
	bool	zero;

	map->highest = INT_MIN;
	map->lowest = INT_MAX;
	while (i < map->y_size)
	{
		if (map->terrain[i].axis[Z] > map->highest)
			map->highest = map->terrain[i].axis[Z];
		if (map->terrain[i].axis[Z] < map->lowest)
			map->lowest = map->terrain[i].axis[Z];
		if (map->terrain[i].axis[Z] == 0)
			zero = true;
		i++;
	}
	map->floor = map->lowest;
	if (zero)
		map->floor = 0;
	
}
