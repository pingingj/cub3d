# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 16:42:33 by dgarcez-          #+#    #+#              #
#    Updated: 2025/08/27 15:50:43 by dpaes-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MLX = 	./incs/minilibx-linux/libmlx.a
LIBFT = ./incs/libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
MLXFLAGS = -L ./minilibx_linux -Imlx_linux -lX11 -lXext

SOURCES = main.c generation/creation.c generation/raycast_math.c generation/raycast_start.c \
			generation/drawing_minimap.c utils/clean.c utils/events.c utils/mlx_adds.c \
			utils/events2.c parser/parser.c parser/rgb_parser.c parser/rgb_converter.c \
			parser/map_parser.c parser/map_create.c 
      
SRCS_DIR = srcs
SRCS =	$(addprefix $(SRCS_DIR)/, $(SOURCES))

OBJS_DIR = objs
OBJ_FILES =  $(addprefix $(OBJS_DIR)/, $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLX) -lm $(MLXFLAGS) -o $(NAME)
	@echo done

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo compiling...
	@make -C ./incs/libft -s

$(MLX):
	@make -C ./incs/minilibx-linux -s
	
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/generation
	@mkdir -p $(OBJS_DIR)/parser
	@mkdir -p $(OBJS_DIR)/utils

clean:
	@make clean -C ./incs/libft -s
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C ./incs/libft -s
	rm -f $(NAME)

re: fclean all

map1: all
	@./$(NAME) maps/map1.ber

map2: all
	@./$(NAME) maps/map2.ber

map3: all
	@./$(NAME) maps/map3.ber