/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_cam_picture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 13:49:00 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/02/03 12:58:41 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** x1	>	p1->cam_x
** y1	>	p1->cam_z
** x2	>	p2->cam_x
** y2	>	p2->cam_z
*/

static double		get_cross_x(t_wolf_point *p1, t_wolf_point *p2
	, double angle)
{
	if ((p2->cam_x == p1->cam_x))
		return (p1->cam_x);
	else if (p1->cam_z == p2->cam_z)
		return (p1->cam_z / tan(angle * DEGREE));
	else
		return (((p1->cam_z * p2->cam_x) - (p1->cam_x * p2->cam_z))
		/ (((p2->cam_x - p1->cam_x) * tan(angle * DEGREE))
		+ p1->cam_z - p2->cam_z));
}

static int			isinwall(t_wolf_point *p1, t_wolf_point *p2
	, double cross_x, double cross_z)
{
	if ((cross_z < 0)
		|| (!(cross_x >= p1->cam_x && cross_x <= p2->cam_x)
			&& !(cross_x <= p1->cam_x && cross_x >= p2->cam_x))
		|| (!(cross_z >= p1->cam_z && cross_z <= p2->cam_z)
			&& !(cross_z <= p1->cam_z && cross_z >= p2->cam_z)))
		return (0);
	return (1);
}

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
	cross_x = get_cross_x(p1, p2, angle);
	cross_z = cross_x * tan(angle * DEGREE);
	if (!isinwall(p1, p2, cross_x, cross_z))
		return (cast_ray(angle, wall->next, ray));
	distance = cross_z;
	if (!ray || ray->distance > distance)
	{
		if (!ray)
			ray = check_malloc(malloc(sizeof(t_wolf_ray)));
		ray->wall = wall;
		ray->distance = distance;
	}
	return (cast_ray(angle, wall->next, ray));
}

static void			draw_column(t_wolf_win *win, int x, double distance
	, int color)
{
	int			i;
	double		wall_height;
	int			max;

	wall_height = (atan(((double)SCOPE / 2) / distance) / DEGREE)
		/ ((double)VIEW_WIDTH / (double)win->width) * 2;
	if (wall_height > win->height)
		wall_height = win->height;
	max = (int)floor((win->height / 2) + (wall_height / 2));
	i = (int)floor((win->height / 2) - (wall_height / 2));
	while (i < max)
	{
		win->img_data[x + (i * win->width)] = color;
		i++;
	}
}

void				gen_cam_picture(t_env *env)
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
		}
		i++;
	}
	mlx_put_image_to_window(env->win->mlx, env->win->win, env->win->img, 0, 0);
}
