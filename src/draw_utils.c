/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:12:19 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/21 10:22:41 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	get_color_gradient(int startcolor, int endcolor, int len, int progress)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	if (len == 0)
		len++;
	increment[0] = (double)((R(endcolor)) - (R(startcolor))) / (double)len;
	increment[1] = (double)((G(endcolor)) - (G(startcolor))) / (double)len;
	increment[2] = (double)((B(endcolor)) - (B(startcolor))) / (double)len;
	new[0] = (R(startcolor)) + round(progress * increment[0]);
	new[1] = (G(startcolor)) + round(progress * increment[1]);
	new[2] = (B(startcolor)) + round(progress * increment[2]);
	newcolor = RGB(new[0], new[1], new[2]);
	return (newcolor);
}

void	set_color(t_image *img, int pixel, int color)
{
	if (img->endian == 1)
	{
		img->buffer[pixel + 0] = 0x0;
		img->buffer[pixel + 1] = R(color);
		img->buffer[pixel + 2] = G(color);
		img->buffer[pixel + 3] = B(color);
	}
	else if (img->endian == 0)
	{
		img->buffer[pixel + 0] = B(color);
		img->buffer[pixel + 1] = G(color);
		img->buffer[pixel + 2] = R(color);
		img->buffer[pixel + 3] = 0x0;
	}
}
#include <stdio.h>

void	print_loaded_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size)
	{
			printf("%.1f,%.1f,%.1f   ", map->terrain[i].axis[X], map->terrain[i].axis[Y], map->terrain[i].axis[Z]);
			i++;
	}
	ft_printf("==============\n\n\n");
}
