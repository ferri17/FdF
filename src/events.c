/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:39:23 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/07 21:24:26 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

int	escape_key_hook(int keycode, void *param)
{
	if (keycode == ESC_KEY)
		close_program(param);
	return (0);
}

int	close_program(void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy(data->mlx);
	exit(0);
}
