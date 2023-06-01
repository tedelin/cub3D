# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 16:28:04 by mcatal-d          #+#    #+#              #
#    Updated: 2023/06/01 18:41:23 by tedelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
INCLUDE 	= -I./include -I./libft -I./mlx
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
HEADERS = include/cub3d.h mlx/mlx.h mlx/mlx_int.h libft/libft.h
SRCS		= 	$(addprefix src/, main.c \
				$(addprefix parsing/, file_to_char.c set_struct_map.c free.c \
				verif_good_map.c check_player.c utils_parsing.c verif_rgb.c) \
				$(addprefix raycasting/, raycasting.c moves.c utils.c))
OBJS		= $(patsubst src/%.c, obj/%.o, $(SRCS))
RM			= rm -rf
LIBFT = -Llibft -lft
MLX_FLAGS	= -Lmlx -lmlx -lX11 -lXext
	
all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	make -C mlx	
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT) -lm

obj/%.o: src/%.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	make -C mlx clean
	make -C libft clean
	$(RM) $(OBJS)
	$(RM) obj


fclean:	clean
	make -C libft fclean
	$(RM) $(NAME)


re:		fclean all

.PHONY: all clean fclean re
