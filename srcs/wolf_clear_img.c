/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_clear_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 16:23:12 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/02/02 18:34:03 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	wolf_clear_img(t_wolf_win *win)
{
	int		i;
	int		j;
	int		width;
	int		height;

	width = win->width;
	height = win->height;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			win->img_data[(i * width) + j] = 0x000000;
			win->img2_data[(i * width) + (j++)] = 0x000000;
		}
		i++;
	}
}
