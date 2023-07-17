/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:50:15 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/17 19:31:47 by fbosch           ###   ########.fr       */
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

/*###	WINDOW SIZE	###*/
# define WIN_W 1000
# define WIN_H 700

/*###	UTILS	###*/
# define ZOOM_IN 1.2
# define ZOOM_OUT 0.8
# define TRANSL 10

/*###	KEY MAPPING	###*/
# define ESC_KEY 0x35
# define PLUS_KEY 0x45
# define MINUS_KEY 0x4E
# define O_KEY 0x1F
# define P_KEY 0x23
# define A_KEY 0x00
# define S_KEY 0x01
# define D_KEY 0x02
# define W_KEY 0x0D
# define T_KEY 0x11

/*###	X11 EVENTS SUPPORTED BY MINILIBX	###*/
# define KEYDOWN 2
# define KEYUP 3
# define MOUSEDOWN 4
# define MOUSEUP 5
# define MOUSEMOVE 6
# define EXPOSE 12
# define DESTROY 17

/*###	MOUSE EVENTS	###*/
# define MID_CLICK 3
# define SCROLL_UP 4
# define SCROLL_DOWN 5

# define X 0
# define Y 1
# define Z 2

/*###	GEOMETRY	###*/
# ifndef M_PI
#  define M_PI
# endif
# define ISO_ANGLE (M_PI/6)
# define NINETY_DEG (M_PI/8)

/*###	COLORS	###*/
# define WHITE 0xFFFFFF	
# define BLACK 0x0
# define DARK_GRAY 0x262626
# define ACQUA 0x36FFDD
# define PINK 0xFFB5FF

/*###	BITSHIFTING	COLOR CHANNELS###*/
# define A(a) (a) >> 24
# define R(a) (a) >> 16 & 0xFF
# define G(a) ((a) >> 8) & 0xFF
# define B(a) (a) & 0xFF
# define RGB(a, b, c) ((a) << 16) + ((b) << 8) + (c)

# include "mlx.h"
# include <fcntl.h>
# include <math.h> //CHECK IF IT HAS TO BE INCLUDED AS MAKEFILE FLAG
# include <stdbool.h>

typedef struct s_key
{
	bool	mid_clicked;
	bool	first_mid_click;
}	t_key;

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

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}	t_line;

typedef struct s_map
{
	int		fd;
	int		x_size;
	int		y_size;
	int		size;
	int		highest;
	int		lowest;
	int		floor;
	//int		z_norm;
	int		gradient[2];
	float	zoom;
	int		translate[2];
	float	rotate[3];
	t_line	line;
	t_point	**terrain;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	t_map	map;
	t_image	img;
	t_key	key;
}	t_mlx;

typedef struct s_bresenh
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;
}	t_bresenh;

/*###   PARSING MAP   ###*/
void	init_data(t_mlx *data);
void	load_map(char *map_dir, t_map *map);
void	get_heights(t_map *map);

/*###   UTILS   ###*/
void	free_terrain(t_map *map, int i);
int		compare_str_end(char *str, char *end);
void	free_and_close(t_mlx *data, t_map *map, t_image *img, int exit_code);
void	error_exit(char *mssg);

/*###   DRAW   ###*/
void	init_visualization(t_mlx *data, t_map *map);
void	draw_map(t_mlx *data, t_map *map);
void	bresenham(t_mlx *data, t_line line, int color0, int color1);
int		my_put_pixel(t_image *img, int x, int y, int color);
void	set_color(t_image *img, int pixel, int color);
void	fill_background(t_mlx *data, int color1, int color2);

/*###   DRAW UTILS  ###*/
int		get_color_gradient(int startcolor, int endcolor, int len, int progress);

/*###	EVENTS	###*/
int		key_down(int key, void *param);
int		mouse_down(int button, int x,int y, void *param);
int		mouse_up(int button, int x,int y, void *param);
int		mouse_move(int x, int y, void *param);
int		close_program(void *param, int exit_code);
void	change_height(void *param, int delta);
void	zoom_screen(void *param, float zoom);
void	move_map(void *param, int key);

/*###	UTILS TO BE DELETED	###*/
void	print_loaded_map(t_map *map);

#endif