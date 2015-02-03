/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_wolf_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 18:22:36 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/02/03 12:02:43 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_wolf_point	*new_wolf_point(int x, int z)
{
	t_wolf_point	*neopoint;

	neopoint = check_malloc(malloc(sizeof(t_wolf_point)));
	neopoint->x = x;
	neopoint->z = z;
	neopoint->cam_x = 0;
	neopoint->cam_z = 0;
	return (neopoint);
}
