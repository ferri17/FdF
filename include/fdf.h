/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:50:15 by fbosch            #+#    #+#             */
/*   Updated: 2023/08/08 15:36:06 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*###	LIBRARIES	###*/
# include "mlx.h"
# include <fcntl.h>
# include <math.h> //CHECK IF IT HAS TO BE INCLUDED AS MAKEFILE FLAG
# include <stdbool.h>
# include <stdint.h>
# include <time.h>

/*###	ERROR MESSAGES	###*/
# define USAGE "Invalid arguments: USAGE [./fdf] [*.fdf]"
# define FILE_ERROR "Error, couldn't open file."
# define ERROR_MAP "Error reading map, make sure it's a valid map."
# define ERROR_MAP_SIZE "Error reading map, minimum width and height is 2."
# define ERROR_MAP_LENGTH "Error reading map, lines have different lengths."
# define UNEXPECTED_ERR "Unexpected error, please run the program again."

/*###	WINDOW SIZES	###*/
# define WIN_W 1400
# define WIN_H 750
# define PAD 50

/*###	MOVEMENTS	###*/
# define ZOOM_IN 1.2
# define ZOOM_OUT 0.8
# define HEIGHT_UP 1.2
# define HEIGHT_DOWN 0.8
# define TRANSL 10
# define ROTATION 3

/*###	KEY MAPPING	###*/
# define ESC_KEY 0x35
# define PLUS_KEY 0x45
# define MINUS_KEY 0x4E
# define ONE_KEY 0x12
# define TWO_KEY 0x13
# define THREE_KEY 0x14
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
# define N_KEY 0x2D
# define M_KEY 0x2E
# define G_KEY 0x05
# define C_KEY 0x08
# define I_KEY 0x22
# define H_KEY 0x04

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
#  define M_PI 3.14159
# endif
# define CUBE_VERTEX 8
# define TOLERANCE 50
# define LEN_DOT 4

/*###	COLORS	###*/
# define WHITE 0xFFFFFF
# define BLACK 0x0
# define GRAY_DARK 0x1A1A1A
# define ACQUA 0x36FFDD
# define PINK 0xFF19A7
# define ORANGE 0xE03E00
# define GREEN 0x12D42A
# define ACQUA_DARK 0x05828E
# define BLUE 0x2286F5
# define BLUE_DARK 0x04018F
# define BROWN 0x8F7027
# define RED 0xFA2828
# define GRAY_LIGHT 0xC7C7C7
# define YELLOW 0xF4DD5B

/*###	MAP THEMES	###*/
# define BG_C 0
# define OBJ1_C 1
# define OBJ2_C 2
# define TEXT 3

/*###	AXIS COLOR	###*/
# define COL_AXIS_X RED
# define COL_AXIS_Y GREEN
# define COL_AXIS_Z BLUE

typedef struct s_key
{
	bool		right_clicked;
	bool		first_right_click;
	bool		left_clicked;
	bool		first_left_click;
	bool		axis_locked[3];
}				t_key;

typedef struct s_image
{
	void		*ptr;
	int			pixel_bits;
	int			line_bytes;
	int			endian;
	char		*buffer;
}				t_image;

typedef struct s_point
{
	float		axis[3];
	int			color;
}				t_point;

typedef struct s_line_draw
{
	int			start[2];
	int			end[2];
}				t_line_draw;

typedef struct s_line
{
	t_point		start;
	t_point		end;
}				t_line;

typedef struct rotation_matrix
{
	float		x[3][3];
	float		y[3][3];
	float		z[3][3];
}				t_mtx;

typedef struct s_map
{
	int			fd;
	int			x_size;
	int			y_size;
	int			size;
	int			highest;
	int			lowest;
	int			theme[4];
	int			col_axis[3];
	double		zoom;
	float		z_resize;
	float		translate[2];
	int			rotate[3];
	t_mtx		r_matrix;
	uint8_t		mode;
	int			t_render;
	t_line		line;
	t_point		*terrain;
	t_point		*obj;
}				t_map;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_map		map;
	t_image		img;
	t_key		key;
}				t_mlx;

typedef struct s_bresenh
{
	t_line_draw	draw;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err2;
	bool		accept;
}				t_bresenh;

typedef struct s_cohen
{
	int			x;
	int			y;
	int			code_start;
	int			code_end;
	int			code_out;
	bool		accept;
}				t_cohen;

/*###   MAP LOAD   ###*/
void			load_map(char *map_dir, t_map *map);
void			map_colors(t_map *map);
void			calculate_start_position(t_mlx *data);

/*###   UTILS   ###*/
void			init_rotation_matrix(t_map *map);
int				compare_str_end(char *str, char *end);
void			error_exit(char *mssg);
void			init_data(t_mlx *data);
void			init_image(t_mlx *data);

/*###   DRAW   ###*/
void			init_visualization(t_mlx *data);
void			draw_map(t_mlx *data, t_map *map);
void			bresenham(t_mlx *data, t_line line);
int				my_put_pixel(t_mlx *data, int x, int y, int color);
void			draw_background(t_mlx *data, int bg_color);

/*###   DRAW UTILS  ###*/
int				get_color_gradient(int startcolor, int endcolor, int len,
					int progress);
void			set_color(t_image *img, int pixel, int color);
void			draw_map_mode(t_mlx *data, t_map *map, int i);
void			draw_dot(t_mlx *data, t_point obj);
void			my_string_put(t_mlx *data, int x, int y, char *text);

/*###   MATRIX  ###*/
void			mult_matrix(t_point *point, float (*matrix)[3]);
void			init_matrix(float matrix[3][3]);
void			calculate_rotation_matrix(float (*matrix)[3], float angle,
					uint8_t axis);
void			calculate_all_rotation_matrix(t_mlx *data);

/*###	EVENTS	###*/
int				key_up(int key, void *param);
int				key_down(int key, void *param);
int				mouse_down(int button, int x, int y, void *param);
int				mouse_up(int button, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);

/*###	EVENT UTILS	###*/
int				close_program(t_mlx *map, int exit_code);
void			change_height(t_mlx *map, int key);
void			move_map(t_mlx *map, int key);
void			change_mode(t_mlx *data);
void			change_theme(t_mlx *data, int key);
void			lock_rotation_axis(t_mlx *data, int key);
void			rotate_object(t_mlx *data, int key);
void			snap_orto_projection(t_mlx *data);
void			translate_map_mouse(t_mlx *data, int x, int y);
void			rotate_map_mouse(t_mlx *data, int x, int y);

/*###	MENU	###*/
void			draw_menu(t_mlx *data);

/*###	CUBE	###*/
void			draw_extras(t_mlx *data);

/*###	ROTATION SPHERE	###*/
void			draw_rotation_sphere(t_mlx *data, int radius);

/*###	COHEN SUTHERLAND	###*/
bool			cohen_sutherland_clipping(float start[3], float end[3]);

#endif