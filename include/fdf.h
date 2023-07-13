/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:50:15 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/13 14:34:11 by fbosch           ###   ########.fr       */
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
# define CROSS_EVENT 17
# define ESC_KEY 53
# define PLUS_KEY 0x45
# define MINUS_KEY 0x4E
# define O_KEY 0x12
# define P_KEY 0x13

# define X 0
# define Y 1

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

typedef struct s_point
{
	int z;
	int	color;
}	t_point;

typedef struct s_map
{
	int		fd;
	int		x_size;
	int		y_size;
	int		size;
	float	zoom;
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	t_point	**terrain;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	t_map	map;
	t_image	img;

}	t_mlx;



typedef struct s_bresenh
{
	int	start[2];
	int	end[2];
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;
}	t_bresenh;

/* typedef struct s_point
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
}	t_map; */

/*###   PARSING MAP   ###*/
void	init_map(t_map *map);
void	load_map(char *map_dir, t_map *map);

/*###   UTILS   ###*/
int		compare_str_end(char *str, char *end);
void	free_and_close(t_mlx *data, t_map *map, t_image *img, int exit_code);

/*###   DRAW   ###*/
void	init_visualization(t_mlx *data, t_map *map);
void	draw_map(t_mlx *data, t_map *map);
void	bresenham(t_map *map, t_image *img);
int		my_put_pixel(t_image *img, int x, int y, int color);
void	set_color(t_image *img, int pixel, int color);
void	fill_background(t_mlx *data, int color);


/*###	EVENTS	###*/
int		key_hook(int keycode, void *param);
int		close_program(void *param, int exit_code);
void	zoom_in(void *param);
void	zoom_out(void *param);

/*###	ERRORS	###*/
void	error_exit(char *mssg);

/*###	UTILS TO BE DELETED	###*/
void	error_exit(char *mssg);
void	print_loaded_map(t_map *map);

#endif