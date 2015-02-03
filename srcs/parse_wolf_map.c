/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wolf_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 15:14:27 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/02/03 12:02:32 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Remember that -1 will immediately become 0 upon first check.
*/

static void		read_map_rows(int *map_data, int fd, int width, int height)
{
	int		i;
	int		ret;
	char	*line;
	char	*str;

	if (height <= 0)
		return ;
	line = NULL;
	ret = get_next_line(fd, &line);
	if (ret < 1)
		wolf3d_error("read_map_rows (1)");
	str = line;
	map_data[0] = ft_atoi(str);
	i = 0;
	while (*(++str) != '\0')
	{
		if (!ft_strchr(ESC_CHARS, *str) && ft_strchr(ESC_CHARS, *(str - 1)))
			map_data[++i] = ft_atoi(str);
		if (i == width)
			wolf3d_error("read_map_rows (2)");
	}
	free(line);
	read_map_rows(map_data + width, fd, width, height - 1);
}

static void		gen_points(t_wolf_point **p, int i, int width)
{
	p[0] = new_wolf_point(((i % width) * SCOPE)
		, ((i / width) * -SCOPE));
	p[1] = new_wolf_point(((i % width) * SCOPE) + SCOPE
		, ((i / width) * -SCOPE));
	p[2] = new_wolf_point(((i % width) * SCOPE)
		, ((i / width) * -SCOPE) - SCOPE);
	p[3] = new_wolf_point(((i % width) * SCOPE) + SCOPE
		, ((i / width) * -SCOPE) - SCOPE);
}

static void		gen_map_walls(t_wolf_map *map, int *data, int size, int width)
{
	int				i;
	t_wolf_point	*p[4];

	i = -1;
	while (++i < size)
	{
		if (data[i])
		{
			gen_points(p, i, width);
			if (!(i % width) || !data[i - 1])
				map->walls = new_wolf_wall(p[2], p[0], RED, map->walls);
			if (!((i + 1) % width) || !data[i + 1])
				map->walls = new_wolf_wall(p[1], p[3], GREEN, map->walls);
			if (!(i / width) || !data[i - width])
				map->walls = new_wolf_wall(p[0], p[1], BLUE, map->walls);
			if (!((i + width) < size) || !data[i + width])
				map->walls = new_wolf_wall(p[3], p[2], YELLOW, map->walls);
		}
		if (data[i] == 2)
			map->cam = new_wolf_cam(((i % width) * SCOPE) + (SCOPE / 2)
				, ((i / width) * -SCOPE) - (SCOPE / 2));
	}
}

static void		read_wolf_map(t_wolf_map *map, int fd, int width, int height)
{
	int		size;

	if (!width || !height)
		wolf3d_error("read_wolf_map (1)");
	size = width * height;
	map->data = check_malloc(malloc(sizeof(int) * (size + 1)));
	read_map_rows(map->data, fd, width, height);
	gen_map_walls(map, map->data, size, width);
	if (!map->cam)
		wolf3d_error("read_wolf_map (2)");
}

t_wolf_map		*parse_wolf_map(char *path)
{
	int				fd;
	t_wolf_map		*map;

	if ((fd = open(path, O_RDONLY)) == -1)
		wolf3d_error("parse_wolf_map");
	map = new_wolf_map();
	read_wolf_map(map, fd, get_file_width(path), get_file_height(path));
	close(fd);
	return (map);
}
