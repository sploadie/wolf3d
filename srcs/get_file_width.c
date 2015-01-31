/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 16:42:07 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/25 16:15:35 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		get_next_line_spill_pop(void)
{
	t_spill	*temp_spill;

	if (!(temp_spill = get_next_line_spill))
		return ;
	get_next_line_spill = get_next_line_spill->next;
	free(temp_spill->text);
	free(temp_spill);
}

size_t	get_file_width(char *path)
{
	int				fd;
	int				ret;
	char			*line;
	int				i;
	size_t			count;

	if ((fd = open(path, O_RDONLY)) == -1)
		wolf3d_error("get_file_with");
	count = 0;
	line = NULL;
	if ((ret = get_next_line(fd, &line)) >= 0)
	{
		i = 0;
		while (line[i] != '\0')
		{
			if (!ft_strchr(ESCAPE_CHARS, line[i]) && (i == 0 || ft_strchr(ESCAPE_CHARS, line[i - 1])))
				count++;
			i++;
		}
	}
	(ret < 0) ? wolf3d_error("get_file_width") : (void)ret;
	close(fd);
	get_next_line_spill_pop();
	return (count);
}
