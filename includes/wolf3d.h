/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/04 16:14:35 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/02/02 18:49:56 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include "wolf_structs.h"
# include "colors.h"

# define DEF_TITLE "WOLF3D Main Window"
# define DEF_X 1000
# define DEF_Y 1000

# define ESCAPE_CHARS " \t"
# define DEGREE 0.0174532925
# define SCOPE 100
# define VIEW_WIDTH 110
# define VELOCITY 10

typedef struct		s_wolf_win
{
	void			*mlx;
	void			*win;
	char			*title;
	int				width;
	int				height;
	void			*img;
	int				*img_data;
	void			*img2;
	int				*img2_data;
	int				img_bits_per_pixel;
	int				img_size_line;
	int				img_endian;
}					t_wolf_win;

typedef struct		s_env
{
	t_wolf_win		*win;
	t_wolf_map		*map;
	t_wolf_cam		*camera;
}					t_env;

void				wolf3d_error(char *str);
void				*check_malloc(void *ret);

int					get_next_line(int fd, char **line);
size_t				get_file_height(char *path);
size_t				get_file_width(char *path);

t_wolf_win			*gen_mlx_window(void *mlx, char *title, int x, int y);

t_wolf_map			*new_wolf_map(void);
t_wolf_cam			*new_wolf_cam(int x, int z);
t_wolf_point		*new_wolf_point(int x, int z);
t_wolf_wall			*new_wolf_wall(t_wolf_point *left, t_wolf_point *right,
												int color, t_wolf_wall *next);
void				new_wolf_img(t_wolf_win *win);
void				wolf_clear_img(t_wolf_win *win);

t_wolf_map			*parse_wolf_map(char *path);
void				gen_cam_points(t_wolf_cam *cam, t_wolf_wall *wall);
void				gen_cam_picture(t_env *env);

int					wolf_key_hook(int keycode, void *env_ptr);

#endif
