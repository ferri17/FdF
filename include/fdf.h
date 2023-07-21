/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:50:15 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/21 21:12:17 by fbosch           ###   ########.fr       */
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

/*###	WINDOW SIZES	###*/
# define WIN_W 1000
# define WIN_H 700
# define PAD 50

/*###	UTILS	###*/
# define ZOOM_IN 1.2
# define ZOOM_OUT 0.8
# define TRANSL 10

/*###	MOVEMENTS	###*/
# define MY_ROTATION 3
# define MY_TRANSLATION 1
# define MY_ZOOM 1

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
# define X_KEY 0x07
# define Y_KEY 0x10
# define Z_KEY 0x06

/*###	X11 EVENTS SUPPORTED BY MINILIBX	###*/
# define KEYDOWN 2
# define KEYUP 3
# define MOUSEDOWN 4
# define MOUSEUP 5
# define MOUSEMOVE 6
# define EXPOSE 12
# define DESTROY 17

/*###	MOUSE EVENTS	###*/
# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define MID_CLICK 3
# define SCROLL_UP 4
# define SCROLL_DOWN 5

# define X 0
# define Y 1
# define Z 2

/*###	MAP MODES	###*/
# define WIRE 30
# define DOT 31

/*###	GEOMETRY	###*/
# define MATRIX_SIZE 3
# ifndef M_PI
#  define M_PI
# endif
# define RADIAN(degree) (degree) * (M_PI / 180)

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
# include <stdio.h> //DELETEEEEE
# include <stdint.h>
# include <time.h>


typedef struct s_key
{
	bool	right_clicked;
	bool	first_right_click;
	bool	left_clicked;
	bool	first_left_click;
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
	float	axis[3];
	int		color;
}	t_point;

typedef struct s_line_draw
{
	int	start[3];
	int	end[3];
}	t_line_draw;

typedef struct s_line
{
	t_point	start;
	t_point	end;
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
	int		gradient[2];
	float	zoom;
	float	translate[2];
	int		rotate[3];
	uint8_t	mode;
	int		t_render;
	t_line	line;
	t_point	*terrain;
	t_point	*obj;
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
	t_line_draw	draw;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		err2;
}	t_bresenh;

/*###   MAP LOAD   ###*/
void	load_map(char *map_dir, t_map *map);
void	map_colors(t_map *map);

/*###   UTILS   ###*/
int		compare_str_end(char *str, char *end);
void	free_and_close(t_mlx *data, t_map *map, t_image *img, int exit_code);
void	error_exit(char *mssg);
void	init_data(t_mlx *data);
void	init_image(t_mlx *data);

/*###   DRAW   ###*/
void	init_visualization(t_mlx *data, t_map *map);
void	draw_map(t_mlx *data, t_map *map);
void	bresenham(t_mlx *data, t_line line);
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

/*###	MENU	###*/
void	draw_menu(t_mlx *data);

/*###	UTILS TO BE DELETED	###*/
void	print_loaded_map(t_map *map);

#endif