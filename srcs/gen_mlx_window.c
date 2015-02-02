/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_mlx_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/04 17:09:11 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/27 15:43:54 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_wolf_win	*gen_mlx_window(void *mlx, char *title, int x, int y)
{
	t_wolf_win	*neowin;

	neowin = check_malloc(malloc(sizeof(t_wolf_win)));
	neowin->win = mlx_new_window(mlx, x, y, title);
	if (!neowin->win)
		wolf3d_error(NULL);
	neowin->mlx = mlx;
	neowin->title = title;
	if (x > INT_MAX)
		wolf3d_error("gen_mlx_window");
	neowin->width = x;
	if (y > INT_MAX)
		wolf3d_error("gen_mlx_window");
	neowin->height = y;
	return (neowin);
}
