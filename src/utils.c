/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:21:16 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/11 00:43:22 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

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
	if(exit_code != EXIT_SUCCESS)
		ft_putstr_fd(UNEXPECTED_ERR, 2);
	close_program(data, exit_code);
}
