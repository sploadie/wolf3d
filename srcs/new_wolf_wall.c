/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_wolf_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 09:51:40 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/26 15:47:03 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_wolf_wall	*new_wolf_wall(t_wolf_point *left, t_wolf_point *right,
	int color, t_wolf_wall *next)
{
	t_wolf_wall	*neowall;

	neowall = check_malloc(malloc(sizeof(t_wolf_wall)));
	neowall->left = left;
	neowall->right = right;
	neowall->color = color;
	neowall->next = next;
	return (neowall);
}
