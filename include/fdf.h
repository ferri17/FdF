/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:50:15 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/12 00:48:27 by fbosch           ###   ########.fr       */
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

# define WHITE 0xFFFFFF	
# define BLACK 0x0
# define ACQUA 0x36FFDD

# include <fcntl.h>
# include <math.h> //CHECK IF IT HAS TO BE INCLUDED AS MAKEFILE FLAG

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
	int	zoom;
	t_point *terrain;
}	t_map;

/*###   PARSING MAP   ###*/
void	init_map(t_map *map);
void	load_map(char *map_dir, t_map *map);

/*###   UTILS   ###*/
int		compare_str_end(char *str, char *end);
void	free_and_close(t_mlx *data, t_map *map, t_image *img, int exit_code);

/*###   DRAW   ###*/
void	print_line(t_image *img, int x0, int y0, int x1, int y1);
int		my_put_pixel(t_image *img, int x, int y, int color);
void	set_color(t_image *img, int pixel, int color);
void	fill_background(t_mlx *data, t_image *img, int color);


/*###	EVENTS	###*/
int		escape_key_hook(int keycode, void *param);
int		close_program(void *param, int exit_code);

/*###	ERRORS	###*/
void	error_exit(char *mssg);

#endif