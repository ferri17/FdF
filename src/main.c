/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:08:24 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/07 21:26:44 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

void	count_width_map(char *line, t_map *map)
{
	char	**args;
	int		i;
	int		aux;

	args = ft_split_str(line, "\t ");
	if (!args)
	{
		close(map->fd);
		free(line);
		error_exit(UNEXPECTED_ERR);
	}
	i = 0;
	aux = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "\n") == 0)
			break ;
		aux++;
		i++;
	}
	free(line);
	ft_free_malloc_array(args, ft_array_len(args));
	if (map->x_size != 0 && map->x_size != aux)
		error_exit(ERROR_MAP_LENGTH);
	map->x_size = aux;
}

void	get_map_info(char *map_dir, t_map *map)
{
	char	*line;

	map->fd = open(map_dir, O_RDONLY);
	if (map->fd < 0)
		error_exit(FILE_ERROR);
	while (1)
	{
		line = get_next_line(map->fd);
		if (line == NULL)
			break ;
		count_width_map(line, map);
		map->y_size++;
	}
	close(map->fd);
	if (map->x_size < 2 || map->y_size < 2)
		error_exit(ERROR_MAP_SIZE);
	map->size = map->x_size * map->y_size;
}

void	fill_terrain(char *line, int y, t_map *map)
{
	static int	i;
	char		**args;
	int			x;

	i = 0;
	args = ft_split_str(line, "\t ");
	if (!args)
	{
		free(line);
		close(map->fd);
		error_exit(UNEXPECTED_ERR);
	}
	x = 0;
	while (args[x])
	{
		if (ft_strcmp(args[x], "\n") == 0)
			break ;
		map->terrain[i].pos[X] = x;
		map->terrain[i].pos[Y] = y;
		map->terrain[i].pos[Z] = ft_atoi(args[x]);
		ft_printf("\r 🚀 Reading points... %i / %i", i + 1, map->size);
		i++;
		x++;
	}
}

void	print_loaded_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size)
	{
		ft_printf("%i,%i,%i   ", map->terrain[i].pos[X], map->terrain[i].pos[Y],
			map->terrain[i].pos[Z]);
		if (map->terrain[i].pos[X] == map->x_size - 1)
			ft_printf("\n");
		i++;
	}
	ft_printf("\n");
	ft_printf("%i,%i,%i   ", map->terrain[i].pos[X], map->terrain[i].pos[Y],
		map->terrain[i].pos[Z]);
}

void	load_map(char *map_dir, t_map *map)
{
	char	*line;
	int		i;

	get_map_info(map_dir, map);
	map->fd = open(map_dir, O_RDONLY);
	if (map->fd < 0)
		error_exit(FILE_ERROR);
	map->terrain = (t_point *)malloc(sizeof(t_point) * map->size);
	if (!map->terrain)
	{
		close(map->fd);
		error_exit(UNEXPECTED_ERR);
	}
	i = 0;
	while (1)
	{
		line = get_next_line(map->fd);
		if (line == NULL)
			break ;
		fill_terrain(line, i, map);
		i++;
	}
	ft_printf("\r ✅ Read a total of %i / %i points \n", map->size, map->size);
	ft_printf("\n\n\n Opening a windows...\n\n\n\n");
	close(map->fd);
}

int	compare_str_end(char *str, char *end)
{
	int	len_str;
	int	len_end;

	len_str = ft_strlen(str);
	len_end = ft_strlen(end);
	return (ft_strcmp(str + len_str - len_end, end));
}

void	init_map(t_map *map)
{
	map->fd = 0;
	map->x_size = 0;
	map->y_size = 0;
	map->size = 0;
	map->terrain = NULL;
}

int	main(int ac, char **av)
{
	t_map	map;
	t_mlx	data;

	if (ac != 2 || compare_str_end(av[1], ".fdf"))
		error_exit(USAGE);
	init_map(&map);
	load_map(av[1], &map);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "My first window");
	mlx_key_hook(data.mlx_win, escape_key_hook, (void *)&data);
	mlx_hook(data.mlx_win, CROSS_EVENT, 0, close_program, (void *)&data);
	mlx_loop(data.mlx);
}
