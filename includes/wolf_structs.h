/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 14:50:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/02/02 18:20:17 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_STRUCTS_H
# define WOLF_STRUCTS_H

typedef struct			s_wolf_point
{
	int					x;
	int					z;
	double				cam_x;
	double				cam_z;
}						t_wolf_point;

typedef struct			s_wolf_wall
{
	t_wolf_point		*left;
	t_wolf_point		*right;
	int					color;
	struct s_wolf_wall	*next;
}						t_wolf_wall;

typedef struct			s_wolf_cam
{
	t_wolf_point		*point;
	double				y_ang;
}						t_wolf_cam;

typedef struct			s_wolf_map
{
	t_wolf_wall			*walls;
	int					*data;
	int					width;
	t_wolf_cam			*cam;
}						t_wolf_map;

typedef struct			s_wolf_ray
{
	double				distance;
	double				cross_z;
	t_wolf_wall			*wall;
}						t_wolf_ray;

/*
typedef struct			s_wolf_node
{
	t_wolf_wall			*wall;
	double				distance;
	struct s_wolf_node	*farther;
	struct s_wolf_node	*closer;
}						t_wolf_node;

typedef struct			s_wolf_tree
{
	struct s_wolf_node	*left;
	struct s_wolf_node	*right;
}						t_wolf_tree;
*/

#endif
