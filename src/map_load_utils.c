/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:27:10 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/22 03:21:26 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static void	get_heights(t_map *map)
{
	int		i;
	bool	zero;

	map->highest = INT_MIN;
	map->lowest = INT_MAX;
	i = 0;
	while (i < map->size)
	{
		if (map->terrain[i].axis[Z] > map->highest)
			map->highest = map->terrain[i].axis[Z];
		if (map->terrain[i].axis[Z] < map->lowest)
			map->lowest = map->terrain[i].axis[Z];
		if (map->terrain[i].axis[Z] == 0)
			zero = true;
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
			map->terrain[i].color = get_color_gradient(map->theme[OBJ1_C],\
				map->theme[OBJ2_C], len, pro);
			i++;
	}
}
