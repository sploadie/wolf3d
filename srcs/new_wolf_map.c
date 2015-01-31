/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_wolf_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 18:11:55 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/27 12:49:48 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_wolf_map	*new_wolf_map(void)
{
	t_wolf_map	*neomap;

	neomap = check_malloc(malloc(sizeof(t_wolf_map)));
	neomap->walls = NULL;
	neomap->data = NULL;
	neomap->width = 0;
	neomap->cam = NULL;
	return (neomap);
}
