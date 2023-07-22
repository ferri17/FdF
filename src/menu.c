/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:23:46 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/22 15:23:09 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void	draw_performance(t_mlx *data)
{
	char	*time;
	char	*render_t;

	time = ft_itoa(data->map.t_render);
	if (!time)
	{
		mlx_string_put(data->mlx, data->mlx_win, WIN_W - (PAD * 2), PAD / 2, WHITE, "error");
		return ;
	}
	render_t = ft_strjoin(time, " ms");
	if (!render_t)
	{
		free (time);
		mlx_string_put(data->mlx, data->mlx_win, WIN_W - (PAD * 2), PAD / 2, WHITE, "error");
		return ;
	}
	mlx_string_put(data->mlx, data->mlx_win, WIN_W - (PAD * 2), PAD / 2, WHITE, render_t);
	free (time);
	free (render_t);
}

void	draw_menu(t_mlx *data)
{
	draw_performance(data);
}