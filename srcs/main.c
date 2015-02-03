/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/04 16:23:47 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/02/03 12:03:12 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_wolf_win	*first_window(void *mlx, int argnum, char **argv)
{
	t_wolf_win	*win;

	if (argnum < 2)
		win = gen_mlx_window(mlx, DEF_TITLE, DEF_X, DEF_Y);
	else if (argnum == 2)
		win = gen_mlx_window(mlx, DEF_TITLE, ft_atoi(argv[1])
			, ft_atoi(argv[1]));
	else if (argnum == 3)
		win = gen_mlx_window(mlx,
			DEF_TITLE, ft_atoi(argv[1]), ft_atoi(argv[2]));
	else if (argnum == 4)
		win = gen_mlx_window(mlx,
			argv[3], ft_atoi(argv[1]), ft_atoi(argv[2]));
	if (!win)
		wolf3d_error(NULL);
	return (win);
}

static int			put_instructions(void)
{
	ft_putstr("Usage: wolf3d [Map] [Size || X Size] [Y Size] [Title]\n");
	exit(0);
}

static void			prep_env(t_env *env, t_wolf_win *win, t_wolf_map *map)
{
	env->win = win;
	env->map = map;
	env->camera = map->cam;
}

int					main(int argc, char **argv)
{
	void			*mlx;
	t_wolf_win		*win;
	t_wolf_map		*map;
	t_env			env;

	if (argc < 2)
		put_instructions();
	ft_putendl("Initializing MLX...");
	mlx = mlx_init();
	if (!mlx)
		wolf3d_error(NULL);
	ft_putendl("Creating window...");
	if (argc == 2)
		win = first_window(mlx, argc - 1, NULL);
	else
		win = first_window(mlx, argc - 1, argv + 1);
	ft_putendl("Parsing map file...");
	map = parse_wolf_map(argv[1]);
	gen_cam_points(map->cam, map->walls);
	new_wolf_img(win);
	prep_env(&env, win, map);
	mlx_key_hook(win->win, wolf_key_hook, &env);
	mlx_expose_hook(win->win, wolf_expose_hook, &env);
	mlx_loop(mlx);
	return (0);
}
