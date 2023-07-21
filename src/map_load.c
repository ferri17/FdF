/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:15:25 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/21 18:43:16 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void	count_width_map(char *line, t_map *map)
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
	ft_free_malloc_array(args, ft_array_len(args) - 1);
	if (map->x_size != 0 && map->x_size != aux)
		error_exit(ERROR_MAP_LENGTH);
	map->x_size = aux;
}

static void	fill_terrain(char *line, int line_n, t_map *map)
{
	static int	i = 0;
	char		**args;
	int			x;

	args = ft_split_str(line, "\t ");
	if (!args)
	{
		free(line);
		free(map->terrain);
		close(map->fd);
		error_exit(UNEXPECTED_ERR);
	}
	x = 0;
	while (args[x])
	{
		if (ft_strcmp(args[x], "\n") == 0)
			break ;
		map->terrain[i].axis[X] = (i % map->x_size) - (map->x_size / 2);
		map->terrain[i].axis[Y] = line_n - (map->y_size / 2);
		map->terrain[i].axis[Z] = ft_atoi(args[x]); //DIVIDE FACTOR TO NORMALIZE HEIGHT MAP
		i++;
		x++;
	}
	ft_free_malloc_array(args, ft_array_len(args) - 1);
}

static void	get_map_info(char *map_dir, t_map *map)
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
		fill_terrain(line, i++, map);
		free(line);
	}
	map_colors(map);
	ft_printf("Read a total of %i points \n", map->size);
	ft_printf("\n\n\n Opening a windows...\n\n\n\n");
	close(map->fd);
}
