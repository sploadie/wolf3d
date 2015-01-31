/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/04 16:23:47 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/31 16:36:36 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_wolf_win	*first_window(void *mlx, int argnum, char **argv)
{
	t_wolf_win	*win;

	if (argnum < 2)
		win = gen_mlx_window(mlx, DEF_TITLE, DEF_X, DEF_Y);
	else if (argnum == 2)
		win = gen_mlx_window(mlx, DEF_TITLE, ft_atoi(argv[1]), ft_atoi(argv[1]));
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

static void	print_debug_map(t_wolf_map *map)
{
	t_wolf_wall	*wall;

	wall = map->walls;
	while (wall)
	{
		ft_putstr("Wall:\t(");
		ft_putnbr(wall->left->x);
		ft_putstr(",\t");
		ft_putnbr(wall->left->z);
		ft_putstr(")\t-> (");
		ft_putnbr(wall->right->x);
		ft_putstr(",\t");
		ft_putnbr(wall->right->z);
		ft_putstr(")\n");
		wall = wall->next;
	}
	ft_putstr("Camera:\t(");
	ft_putnbr(map->cam->point->x);
	ft_putstr(",\t");
	ft_putnbr(map->cam->point->z);
	ft_putstr(")\tAngle: ");
	printf("%f\n", map->cam->y_ang);//FIXME
}

static void	print_debug_cam_map(t_wolf_map *map)
{
	t_wolf_wall	*wall;

	wall = map->walls;
	while (wall)
	{
		ft_putstr("Wall:\t(");
		ft_putnbr(wall->left->cam_x);
		ft_putstr(",\t");
		ft_putnbr(wall->left->cam_z);
		ft_putstr(")\t-> (");
		ft_putnbr(wall->right->cam_x);
		ft_putstr(",\t");
		ft_putnbr(wall->right->cam_z);
		ft_putstr(")\n");
		wall = wall->next;
	}
	ft_putstr("Camera:\t(");
	ft_putnbr(map->cam->point->cam_x);
	ft_putstr(",\t");
	ft_putnbr(map->cam->point->cam_z);
	ft_putstr(")\tAngle: ");
	printf("%f\n", map->cam->y_ang);//FIXME
}

int			main(int argc, char **argv)
{
	void			*mlx;
	t_wolf_win		*win;
	t_wolf_map		*map;
	t_env			env;

	//Need at least map
	if (argc < 2)
	{
		ft_putstr("Usage: FDF [Map] [Size || X Size] [Y Size] [Title]\n");
		return (0);
	}

	//Get the mlx pointer;
	ft_putendl("Initializing MLX...");
	mlx = mlx_init();
	if (!mlx)
		wolf3d_error(NULL);

	//Generate the window
	ft_putendl("Creating window...");
	if (argc == 2)
		win = first_window(mlx, argc - 1, NULL);
	else
		win = first_window(mlx, argc - 1, argv + 1);

	//Get Map
	ft_putendl("Parsing map file...");
	map = parse_wolf_map(argv[1]);

	//Print Map
	ft_putendl("Original Map:");
	print_debug_map(map);

	//Gen Camera
	gen_cam_points(map->cam, map->walls);

	//Print Camera Map
	ft_putendl("Camera Map:");
	print_debug_cam_map(map);

	//Gen Image
	new_wolf_img(win);

	//Set up environment for hooks
	env.win = win;
	env.map = map;
	env.camera = map->cam;

	gen_cam_picture(&env);

	//Set up hooks and initialize loop
	mlx_key_hook(win->win, wolf_key_hook, &env);
	// mlx_mouse_hook(win->win, wolf_mouse_hook, &env);
	// mlx_expose_hook(win->win, wolf_expose_hook, &env);
	// mlx_loop_hook(mlx, fdf_loop_hook, &env);
	mlx_loop(mlx);

	//===================CURRENT TRANSFER FROM FDF POINT===================//

	// //Gen empty map for camera
	// //Transform map -> camera map.
	// camera = gen_default_camera();
	// cam_map = wolf_map(map->width, map->height);
	// trans_wolf_map(cam_map, map, camera);

	return (0);
}
