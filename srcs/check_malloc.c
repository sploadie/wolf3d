/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:54:12 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/25 13:56:43 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	*check_malloc(void *ret)
{
	if (ret)
		return (ret);
	wolf3d_error(NULL);
	return (NULL);
}
