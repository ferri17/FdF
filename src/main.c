/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:08:24 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/06 01:20:45 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

void	get_map_lines(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	if (line == NULL)
		error_exit(ERROR_MAP);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	map->y_size = i;
}
#include <sys/wait.h>

void	load_map(char *map_dir, t_map *map)
{
	int		fd;

	fd = open(map_dir, O_RDONLY);
	if (fd < 0)
		error_exit(NO_FILE);
	get_map_lines(fd, map);
	ft_printf("Map y size is %i\n", map->y_size);
	map->points = (int **)malloc(sizeof(int *) * map->y_size);
	if (!map->points)
		error_exit(UNEXPECTED_ERR);
	exit(0);
	/* while (1)
	{
		line = get_next_line(fd);

		map->y_size++;
		if (line == NULL)
			break ;
	} */
	
}

void	init_map(t_map *map)
{
	map->points = NULL;
	map->x_size = 0;
	map->y_size = 0;
	map->size = 0;
}

int	main(int ac, char **av)
{
	t_mlx	data;
	t_map	map;

	if (ac != 2)
		error_exit(USAGE);
	init_map(&map);
	load_map(av[1], &map);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "My first window");
	mlx_key_hook(data.mlx_win, escape_key_hook, (void *)&data);
	mlx_hook(data.mlx_win, 17, 0, close_program, (void *)&data);
	mlx_loop(data.mlx);
}
