/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_wolf_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 10:14:23 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/31 19:00:49 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_wolf_cam	*new_wolf_cam(int x, int z)
{
	t_wolf_cam	*neocam;

	neocam = check_malloc(malloc(sizeof(t_wolf_cam)));
	neocam->point = new_wolf_point(x, z);
	neocam->y_ang = 0;
	return (neocam);
}
