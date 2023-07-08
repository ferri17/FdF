/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:50:15 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/08 11:47:56 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define USAGE "Invalid arguments: USAGE [./fdf] [*.fdf]"
# define FILE_ERROR "Error, couldn't open file."
# define ERROR_MAP "Error reading map, make sure it's a valid map."
# define ERROR_MAP_SIZE "Error reading map, minimum width and height is 2."
# define ERROR_MAP_LENGTH "Error reading map, lines have different lengths."
# define UNEXPECTED_ERR "Unexpected error, please run the program again."
/*#define ERROR(number) "Error [" #number "]" */

# define WIN_W 1000
# define WIN_H 700
# define ESC_KEY 53
# define CROSS_EVENT 17

# define X 0
# define Y 1
# define Z 2

# define ROCKET "\xF0\x9F\x9A\x80"	

# include <fcntl.h>

typedef struct s_image
{
	void	*ptr;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buffer;
}	t_image;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
}	t_mlx;

typedef struct s_point
{
	int pos[3];
}	t_point;

typedef struct s_map
{
	int	fd;
	int	x_size;
	int	y_size;
	int	size;
	t_point *terrain;
}	t_map;

/*###   PARSING MAP   ###*/
void	init_map(t_map *map);
void	load_map(char *map_dir, t_map *map);

/*###   UTILS   ###*/
int		compare_str_end(char *str, char *end);

/*###	EVENTS	###*/
int		escape_key_hook(int keycode, void *param);
int		close_program(void *param);

/*###	ERRORS	###*/
void	error_exit(char *mssg);

#endif