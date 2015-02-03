/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_spill.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 12:25:22 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/02/03 13:00:08 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_spill		*get_next_line_spill(t_spill *input, int in)
{
	static t_spill	*spill = NULL;

	if (in)
		spill = input;
	return (spill);
}
