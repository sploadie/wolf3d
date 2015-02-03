/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_wolf_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 13:02:00 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/02/03 11:22:09 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	new_wolf_img(t_wolf_win *win)
{
	win->img = mlx_new_image(win->mlx, win->width, win->height);
	win->img_bits_per_pixel = 0;
	win->img_size_line = 0;
	win->img_endian = 0;
	win->img_data = (int *)mlx_get_data_addr(win->img,
									&(win->img_bits_per_pixel),
									&(win->img_size_line),
									&(win->img_endian));
	ft_putstr("\nIMAGE DATA: \n");
	ft_putstr("img_bits_per_pixel: ");
	ft_putnbr(win->img_bits_per_pixel);
	ft_putstr("\nimg_endian: ");
	ft_putnbr(win->img_endian);
	ft_putstr("\nimg_size_line: ");
	ft_putnbr(win->img_size_line);
	write(1, "\n", 1);
}
