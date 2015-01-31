/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wolf_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 15:14:27 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/31 18:33:10 by tgauvrit         ###   ########.fr       */
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
	map_data[(i = 0)] = ft_atoi((str = line));
	while (*(++str) != '\0')
	{
		if (!ft_strchr(ESCAPE_CHARS, *str) && ft_strchr(ESCAPE_CHARS, *(str - 1)))
			map_data[++i] = ft_atoi(str);
		if (i == width)
			wolf3d_error("read_map_rows (2)");
	}
	free(line);
	read_map_rows(map_data + width, fd, width, height - 1);
}

static void		gen_map_walls(t_wolf_map *map, int *data, int size, int width)
{
	int		i;
	t_wolf_point	*p_a;
	t_wolf_point	*p_b;
	t_wolf_point	*p_c;
	t_wolf_point	*p_d;

	i = -1;
	while (++i < size)
	{
		 if (data[i])
		 {
		 	p_a = new_wolf_point(((i % width) * SCOPE), 		((i / width) * -SCOPE));
		 	p_b = new_wolf_point(((i % width) * SCOPE) + SCOPE, ((i / width) * -SCOPE));
		 	p_c = new_wolf_point(((i % width) * SCOPE), 		((i / width) * -SCOPE) - SCOPE);
		 	p_d = new_wolf_point(((i % width) * SCOPE) + SCOPE, ((i / width) * -SCOPE) - SCOPE);
		 	if (!(i % width) || !data[i - 1])				//MAKE LEFT WALL
		 		map->walls = new_wolf_wall(p_c, p_a, RED, map->walls);
		 	if (!((i + 1) % width) || !data[i + 1])			//MAKE RIGHT WALL
		 		map->walls = new_wolf_wall(p_b, p_d, GREEN, map->walls);
		 	if (!(i / width) || !data[i - width])			//MAKE TOP WALL
		 		map->walls = new_wolf_wall(p_a, p_b, BLUE, map->walls);
		 	if (!((i + width) < size) || !data[i + width])	//MAKE BOTTOM WALL
		 		map->walls = new_wolf_wall(p_d, p_c, YELLOW, map->walls);
		 }
		 if (data[i] == 2)
		 	map->cam = new_wolf_cam(((i % width) * SCOPE) + (SCOPE / 2), ((i / width) * -SCOPE) - (SCOPE / 2));
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
