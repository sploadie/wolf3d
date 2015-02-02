/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_key_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 16:21:09 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/02/02 17:23:43 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		wolf_key_hook(int keycode, void *env_ptr)
{
	t_env	*env;

	env = env_ptr;
	if (keycode == 65307)
	{
		//Exit if Esc
		ft_putendl("Esc");
		exit(0);
	}
	// else if (keycode == 65361)
	// {
	// 	ft_putendl("Arrow Left");
	// 	env->camera->z_ang -= 1;
	// }
	// else if (keycode == 65362)
	// {
	// 	ft_putendl("Arrow Up");
	// 	env->camera->point->y += 1;
	// }
	// else if (keycode == 65363)
	// {
	// 	ft_putendl("Arrow Right");
	// 	env->camera->z_ang += 1;
	// }
	// else if (keycode == 65364)
	// {
	// 	ft_putendl("Arrow Down");
	// 	env->camera->point->y -= 1;
	// }
	// else if (keycode == 59)
	// {
	// 	ft_putendl("Key ;");
	// 	env->camera->point->z += 1;
	// }
	// else if (keycode == 47)
	// {
	// 	ft_putendl("Key /");
	// 	env->camera->point->z -= 1;
	// }
	else if (keycode == 113)
	{
		ft_putendl("Key Q");
		env->camera->y_ang += VELOCITY;
	}
	else if (keycode == 119)
	{
		ft_putendl("Key W");
		env->camera->point->x += (int)round(VELOCITY * cos((env->camera->y_ang + 90) * DEGREE));
		env->camera->point->z += (int)round(VELOCITY * sin((env->camera->y_ang + 90) * DEGREE));
	}
	else if (keycode == 101)
	{
		ft_putendl("Key E");
		env->camera->y_ang -= VELOCITY;
	}
	else if (keycode == 97)
	{
		ft_putendl("Key A");
		env->camera->point->x -= (int)round(VELOCITY * cos((env->camera->y_ang) * DEGREE));
		env->camera->point->z -= (int)round(VELOCITY * sin((env->camera->y_ang) * DEGREE));
	}
	else if (keycode == 115)
	{
		ft_putendl("Key S");
		env->camera->point->x -= (int)round(VELOCITY * cos((env->camera->y_ang + 90) * DEGREE));
		env->camera->point->z -= (int)round(VELOCITY * sin((env->camera->y_ang + 90) * DEGREE));
	}
	else if (keycode == 100)
	{
		ft_putendl("Key D");
		env->camera->point->x += (int)round(VELOCITY * cos((env->camera->y_ang) * DEGREE));
		env->camera->point->z += (int)round(VELOCITY * sin((env->camera->y_ang) * DEGREE));
	}
	// else if (keycode == 45)
	// {
	// 	ft_putendl("Key -/_");
	// 	env->camera->zoom -= 1;
	// }
	// else if (keycode == 61)
	// {
	// 	ft_putendl("Key =/+");
	// 	env->camera->zoom += 1;
	// }
	// else if (keycode == 49)
	// {
	// 	ft_putendl("Key 1");
	// 	env->camera->z_shift -= 1;
	// }
	// else if (keycode == 50)
	// {
	// 	ft_putendl("Key 2");
	// 	env->camera->z_shift += 1;
	// }
	// else if (keycode == 51)
	// {
	// 	ft_putendl("Key 3");
	// 	env->camera->gradient -= 1;
	// }
	// else if (keycode == 52)
	// {
	// 	ft_putendl("Key 4");
	// 	env->camera->gradient += 1;
	// }
	else
	{
		write(1, "Key: ", 5);
		ft_putnbr(keycode);
		write(1, "\n", 1);
		return(0);
	}
	printf("Camera: (%i, %i) angle: %f\n", env->camera->point->x, env->camera->point->z, env->camera->y_ang);//FIXME
	ft_putstr("Clear Image... ");
	wolf_clear_img(env->win);
	ft_putstr("Regen Camera Map... ");
	gen_cam_points(env->map->cam, env->map->walls);
	ft_putstr("Redrawing Image... ");
	gen_cam_picture(env);
	ft_putendl("done.");
	return (0);
}
