# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 16:28:04 by mcatal-d          #+#    #+#              #
#    Updated: 2023/05/30 16:23:30 by tedelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
INCLUDE 	= -I./include -I./libft -I./minilibx-linux
CC			= cc
CFLAGS		= -g3#-Wall -Wextra -Werror -g3
SRCS		= 	$(addprefix src/, \
				main.c \
				$(addprefix parsing/, file_to_char.c set_struct_map.c \
							verif_good_map.c free.c check_player.c utils_parsing.c \
							verif_rgb.c) \
				$(addprefix raycasting/, raycasting.c moves.c utils.c))
OBJS		= $(patsubst src/%.c, obj/%.o, $(SRCS))
RM			= rm -rf
MLX_FLAGS	= -lX11 -lXext
	
all:			$(NAME)

libft/libft.a:
	make -C libft

minilibx-linux/libmlx.a:
	make -C minilibx-linux	

$(NAME):		$(OBJS) libft/libft.a minilibx-linux/libmlx.a
				$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) libft/libft.a minilibx-linux/libmlx.a $(MLX_FLAGS) -lm

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
		make -C minilibx-linux clean
		make -C libft clean
		$(RM) $(OBJS)
		$(RM) obj


fclean:	clean
		make -C libft fclean
		$(RM) $(NAME)


re:		fclean all

.PHONY: all clean fclean re
