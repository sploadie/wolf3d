/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_cam_picture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 13:49:00 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/02/02 17:21:59 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*

x1	>	p1->cam_x

y1	>	p1->cam_z

x2	>	p2->cam_x

y2	>	p2->cam_z

*/

// static void			print_wall(t_wolf_wall *wall)
// {
// 	ft_putstr("Wall:\t(");
// 	ft_putnbr(wall->left->cam_x);
// 	ft_putstr(",\t");
// 	ft_putnbr(wall->left->cam_z);
// 	ft_putstr(")\t-> (");
// 	ft_putnbr(wall->right->cam_x);
// 	ft_putstr(",\t");
// 	ft_putnbr(wall->right->cam_z);
// 	ft_putstr(")\n");
// }

// static void			print_ray_check(int cross_x, int x1, int x2)
// {
// 	ft_putstr("cross_x (");
// 	ft_putnbr(cross_x);
// 	ft_putstr(") is in between x1 (");
// 	ft_putnbr(x1);
// 	ft_putstr(") and x2 (");
// 	ft_putnbr(x2);
// 	ft_putstr(")\n");
// }

static t_wolf_ray	*cast_ray(double angle, t_wolf_wall *wall, t_wolf_ray *ray)
{
	t_wolf_point	*p1;
	t_wolf_point	*p2;
	double			cross_x;
	double			cross_z;
	double			distance;

	if (!wall)
		return (ray);
	p1 = wall->left;
	p2 = wall->right;
	//Get X of intersection point
	if ((p2->cam_x == p1->cam_x))
		cross_x = p1->cam_x;
	else if (p1->cam_z == p2->cam_z)
		cross_x = p1->cam_z / tan(angle * DEGREE);
	else
		cross_x = ((p1->cam_z * p2->cam_x) - (p1->cam_x * p2->cam_z)) / (((p2->cam_x - p1->cam_x) * tan(angle * DEGREE)) + p1->cam_z - p2->cam_z);
	cross_z = cross_x * tan(angle * DEGREE);
	//Check if intersection X is not wall
	if (cross_z < 0)
		return (cast_ray(angle, wall->next, ray));
	if (!(cross_x >= p1->cam_x && cross_x <= p2->cam_x) && !(cross_x <= p1->cam_x && cross_x >= p2->cam_x))
	{
		// printf("Cross_x check failed: cross_x: %f p1->cam_x: %f p2->cam_x: %f\n", cross_x, p1->cam_x, p2->cam_x);
		return (cast_ray(angle, wall->next, ray));
	}
	if (!(cross_z >= p1->cam_z && cross_z <= p2->cam_z) && !(cross_z <= p1->cam_z && cross_z >= p2->cam_z))
	{
		// printf("Cross_x check failed: cross_z: %f p1->cam_z: %f p2->cam_z: %f\n", cross_z, p1->cam_z, p2->cam_z);
		return (cast_ray(angle, wall->next, ray));
	}
	// print_ray_check(cross_x, p1->cam_x, p2->cam_x);//FIXME
	// if (angle > 0 && cross_z > 0)
	// 	return (cast_ray(angle, wall->next, ray));
	// if (abs(angle) > 1 && cross_z > 0)
	// 	return (cast_ray(angle, wall->next, ray));
	//DISTANCE T1
	// distance = sqrt((cross_x * cross_x) + (cross_z * cross_z));
	//DISTANCE T2
	distance = cross_z;
	//DISTANCE T3
	// distance = abs(sqrt((cross_x * cross_x) + (cross_z * cross_z)) * sin(angle * DEGREE));
	//DISTANCE T4
	// distance = (((p2->cam_z - p1->cam_z) / (p2->cam_x - p1->cam_x)) * (cross_x - p1->cam_x)) + p1->cam_z;
	if (!ray)
	{
		// ft_putstr("\nRay generated.");//FIXME
		ray = check_malloc(malloc(sizeof(t_wolf_ray)));
		ray->wall = wall;
		ray->distance = distance;
	}
	else if (ray->distance > distance)
	{
		// ft_putstr("\nRay changed.");//FIXME
		// print_wall(wall);//FIXME
		ray->wall = wall;
		ray->distance = distance;
	}
	return (cast_ray(angle, wall->next, ray));
	// return (ray);
}

static void	draw_column(t_wolf_win *win, int x, double distance, int color)
{
	int			i;
	// double		height_percent;
	double		wall_height;
	int			max;

	// height_percent = 100.0 - (distance / 10.0);
	// if (height_percent < 0)
	// 	height_percent = 0;
	// wall_height = (win->height * height_percent) / 100;
	// // wall_height = (win->height + 50) - distance;
	wall_height = (atan(((double)SCOPE / 2) / distance) / DEGREE) / ((double)VIEW_WIDTH / (double)win->width) * 2;
	if (wall_height > win->height)
		wall_height = win->height;
	max = (int)floor((win->height / 2) + (wall_height / 2));
	i  = (int)floor((win->height / 2) - (wall_height / 2));
	while (i < max)
	{
		win->img_data[x + (i * win->width)] = color;
		i++;
	}
}

void	gen_cam_picture(t_env *env)
{
	int			i;
	double		angle;
	double		angle_add;
	t_wolf_ray	*ray;

	angle_add = (double)VIEW_WIDTH / (double)env->win->width;
	angle = ((((double)env->win->width) / 2) * angle_add) + 90 + angle_add;
	i = 0;
	while (i < env->win->width)
	{
		ray = cast_ray((angle -= angle_add), env->map->walls, NULL);
		if (ray)
		{
			draw_column(env->win, i, ray->distance, ray->wall->color);
			// printf("Angle: %f, %f i: %i, Distance: %f\n", angle, tan(angle * DEGREE), i, ray->distance);//FIXME
			// printf("Wall: %#x, left: (%4f, %4f), right: (%4f, %4f)\n", ray->wall->color, ray->wall->left->cam_x, ray->wall->left->cam_z, ray->wall->right->cam_x, ray->wall->right->cam_z);//FIXME
		}
		// else//FIXME
		// 	printf("NO WALL: Angle: %f %f\n", angle, tan(angle * DEGREE));//FIXME
		i++;
	}
	mlx_put_image_to_window(env->win->mlx, env->win->win, env->win->img, 0, 0);
}
