/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_cam_points.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 12:51:50 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/31 19:00:40 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	gen_cam_points(t_wolf_cam *cam, t_wolf_wall *wall)
{
	double		temp;

	if (!wall)
		return ;
	if (cam->y_ang == 0)
		cam->y_ang = 360;
	wall->left->cam_x = wall->left->x - cam->point->x;
	wall->left->cam_z = wall->left->z - cam->point->z;
	wall->right->cam_x = wall->right->x - cam->point->x;
	wall->right->cam_z = wall->right->z - cam->point->z;
	temp = wall->right->cam_z;
	wall->right->cam_z = (wall->right->cam_z * cos(cam->y_ang * DEGREE)) - (wall->right->cam_x * sin(cam->y_ang * DEGREE));
	wall->right->cam_x = (wall->right->cam_x * cos(cam->y_ang * DEGREE)) + (temp * sin(cam->y_ang * DEGREE));
	temp = wall->left->cam_z;
	wall->left->cam_z = (wall->left->cam_z * cos(cam->y_ang * DEGREE)) - (wall->left->cam_x * sin(cam->y_ang * DEGREE));
	wall->left->cam_x = (wall->left->cam_x * cos(cam->y_ang * DEGREE)) + (temp * sin(cam->y_ang * DEGREE));
	gen_cam_points(cam, wall->next);
}