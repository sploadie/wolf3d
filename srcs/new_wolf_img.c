/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_wolf_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 13:02:00 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/27 13:17:53 by tgauvrit         ###   ########.fr       */
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
	// if (win->img_bits_per_pixel != 8)
	// 	wolf_error("new_wolf_img");
	// if (win->img_endian != 1)
	// 	wolf_error("new_wolf_img");
	// if ((unsigned int)win->img_size_line != win->width * 8)
	// 	wolf_error("new_wolf_img");
	ft_putstr("\nIMAGE DATA: \n");//FIXME
	ft_putstr("img_bits_per_pixel: ");//FIXME
	ft_putnbr(win->img_bits_per_pixel);//FIXME
	ft_putstr("\nimg_endian: ");//FIXME
	ft_putnbr(win->img_endian);//FIXME
	ft_putstr("\nimg_size_line: ");//FIXME
	ft_putnbr(win->img_size_line);//FIXME
	write(1, "\n", 1);
}
