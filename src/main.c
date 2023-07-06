/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:08:24 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/06 21:09:48 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

void	get_map_lines(char *map_dir, t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(map_dir, O_RDONLY);
	if (fd < 0)
		error_exit(NO_FILE);
	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		error_exit(ERROR_MAP);
	}
	i = 0;
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	map->y_size = i;
	close(fd);
}
#include <sys/wait.h>

void	load_map(char *map_dir, t_map *map)
{
	char	**matrix;
	char	*line;
	int		fd;
	int		i;

	get_map_lines(map_dir, map);
	map->points = (int **)malloc(sizeof(int *) * map->y_size);
	if (!map->points)
		error_exit(UNEXPECTED_ERR);
	fd = open(map_dir, O_RDONLY);
	if (fd < 0)
		error_exit(NO_FILE);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		matrix = ft_split(line, ' ');
		if (!matrix)
			return (ft_free_malloc_array(matrix, ft_array_len(matrix)));
		/* for (int i = 0; matrix[i]; i++)
			ft_printf("%s ", matrix[i]); */
		i = 0;
		while (ft_strcmp(matrix[i], "\n") != 0)
		{
			ft_printf("%i ", ft_atoi(matrix[i]));
			if (ft_strchr(matrix[i], '\n') != NULL)
				break ;
			i++;
		}
		ft_printf("\n");
		free(line);
		ft_free_malloc_array(matrix, ft_array_len(matrix));
	}
	free(line);
	/* for (int i = 0; i < map->y_size; i++)
	{
		for (int j = 0; matrix[i][j]; j++)
		{
			ft_printf("%s ", matrix[i][j]);
		}
		ft_printf("\n");m
	} */
	/* for (int i = 0; i < map->y_size; i++)
	{
		for (int j = 0; map->points[i][j]; j++)
		{

		}
	} */
	close(fd);
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
	//t_mlx	data;
	t_map	map;

	if (ac != 2)
		error_exit(USAGE);
	init_map(&map);
	load_map(av[1], &map);
	/* data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "My first window");
	mlx_key_hook(data.mlx_win, escape_key_hook, (void *)&data);
	mlx_hook(data.mlx_win, 17, 0, close_program, (void *)&data);
	mlx_loop(data.mlx); */
}
