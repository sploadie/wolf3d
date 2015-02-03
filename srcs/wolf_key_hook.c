/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_key_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 16:21:09 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/02/03 11:35:02 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	movement(int keycode, t_wolf_cam *cam)
{
	if (keycode == 119)
	{
		cam->point->x += (int)round(VELOCITY * cos((cam->y_ang + 90) * DEGREE));
		cam->point->z += (int)round(VELOCITY * sin((cam->y_ang + 90) * DEGREE));
	}
	else if (keycode == 97)
	{
		cam->point->x -= (int)round(VELOCITY * cos((cam->y_ang) * DEGREE));
		cam->point->z -= (int)round(VELOCITY * sin((cam->y_ang) * DEGREE));
	}
	else if (keycode == 115)
	{
		cam->point->x -= (int)round(VELOCITY * cos((cam->y_ang + 90) * DEGREE));
		cam->point->z -= (int)round(VELOCITY * sin((cam->y_ang + 90) * DEGREE));
	}
	else if (keycode == 100)
	{
		cam->point->x += (int)round(VELOCITY * cos((cam->y_ang) * DEGREE));
		cam->point->z += (int)round(VELOCITY * sin((cam->y_ang) * DEGREE));
	}
	else
		return (0);
	return (1);
}

int			wolf_key_hook(int keycode, void *env_ptr)
{
	t_env	*env;

	env = env_ptr;
	if (keycode == 65307)
		exit(0);
	else if (keycode == 113)
		env->camera->y_ang += VELOCITY;
	else if (keycode == 101)
		env->camera->y_ang -= VELOCITY;
	else if (movement(keycode, env->camera))
		ft_putstr("Movement: ");
	else
		return (0);
	ft_putstr("Clear Image... ");
	wolf_clear_img(env->win);
	ft_putstr("Regen Camera Map... ");
	gen_cam_points(env->map->cam, env->map->walls);
	ft_putstr("Redrawing Image... ");
	gen_cam_picture(env);
	ft_putendl("done.");
	return (0);
}
