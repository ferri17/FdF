/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:50:15 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/06 01:12:14 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define USAGE "Invalid arguments: USAGE [./fdf] [map]."
# define NO_FILE "Error, couldn't open file."
# define ERROR_MAP "Error while reading map, make sure it's a valid map."
# define UNEXPECTED_ERR "Unexpected error, please run the program again"
/*#define ERROR(number) "Error [" #number "]" */

# define WIDTH 1350
# define HEIGHT 800
# define ESC_KEY 53

# include <fcntl.h>

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
}	t_mlx;

typedef struct s_map
{
	int	**points;
	int	x_size;
	int	y_size;
	int	size;
}	t_map;


/*###	UTILS	###*/
int		escape_key_hook(int keycode, void *param);
int		close_program(void *param);

/*###	ERRORS	###*/
void	error_exit(char *mssg);

#endif