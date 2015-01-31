# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/20 16:35:37 by tgauvrit          #+#    #+#              #
#    Updated: 2015/01/27 16:34:49 by tgauvrit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			wolf3d

CC =			gcc

FLAGS =			-Wall -Werror -Wextra -g

HEADER =		wolf3d.h get_next_line.h colors.h wolf_structs.h

HEADER_DIR =	-I ./includes/ -I $(FT_LIB_DIR)

MLX_LIBS =		-L/usr/X11/lib -lmlx -lXext -lX11

LIBRARIES =		-L$(FT_LIB_DIR) -l$(FT_LIB_NAME) $(MLX_LIBS)

FT_LIB_NAME =	ft

FT_LIB =		$(FT_LIB_DIR)lib$(FT_LIB_NAME).a

FT_LIB_DIR =	./libft/

SRC_DIR =		./srcs/

SRC_COMPILED =	main.o \
				wolf3d_error.o \
				get_next_line.o \
				get_file_height.o \
				get_file_width.o \
				check_malloc.o \
				gen_mlx_window.o \
				new_wolf_point.o \
				new_wolf_wall.o \
				new_wolf_cam.o \
				new_wolf_map.o \
				new_wolf_img.o \
				parse_wolf_map.o \
				gen_cam_points.o \
				gen_cam_picture.o \
				wolf_clear_img.o \
				wolf_key_hook.o

COMPILED =		$(SRC_COMPILED)

all: $(NAME)

$(NAME): $(FT_LIB) $(SRC_COMPILED)
	$(CC) -o $(NAME) $(FLAGS) $(LIBRARIES) $(HEADER_DIR) $(SRC_COMPILED)

$(SRC_COMPILED): %.o: $(SRC_DIR)%.c
	$(CC) -c $(FLAGS) $(HEADER_DIR) $< -o $@

$(FT_LIB):
	@make -C $(FT_LIB_DIR);

clean:
	make clean -C $(FT_LIB_DIR)
	-/bin/rm -f $(COMPILED)

fclean: clean
	make fclean -C $(FT_LIB_DIR)
	-/bin/rm -f $(NAME)

re: fclean all
