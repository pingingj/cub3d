# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 16:42:33 by dgarcez-          #+#    #+#              #
#    Updated: 2025/12/02 18:11:20 by dpaes-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MLX = 	./incs/minilibx-linux/libmlx.a
LIBFT = ./incs/libft/libft.a

CC = cc -O3
CFLAGS = -Wall -Wextra -Werror -g 
MLXFLAGS = -L ./minilibx_linux -Imlx_linux -lX11 -lXext

SOURCES = main.c generation/creation.c generation/raycast_math.c generation/frame_building.c generation/flashlight.c \
			generation/drawing_minimap.c generation/raycast_hit.c generation/paint.c utils/clean.c utils/door_list.c utils/events.c \
			generation/main_menu.c utils/events2.c utils/mlx_adds.c utils/keys.c utils/movement.c utils/look.c \
			utils/fps.c utils/image_handle.c utils/img_scaling.c utils/draw_mini_arrow.c utils/drawing_mini_aux.c utils/mouse_handle.c \
			parser/parser.c utils/parser_utils.c parser/parse_textures.c parser/rgb_parser.c parser/rgb_converter.c parser/map_parser.c \
			parser/map_parser_aux.c parser/map_create.c parser/make_enemy.c parser/textures.c \
			sprites/monster.c sprites/monster_aux.c sprites/monster_pathfinding.c \
			sprites/monster_path_finding_aux.c generation/sprites_functions.c generation/sprite_functions_aux.c 
       
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
	@make bonus -C ./incs/libft -s

$(MLX):
	@make -C ./incs/minilibx-linux -s
	
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/generation
	@mkdir -p $(OBJS_DIR)/parser
	@mkdir -p $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR)/sprites

clean:
	@make clean -C ./incs/libft -s
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C ./incs/libft -s
	rm -f $(NAME)

re: fclean all

map1: all
	@./$(NAME) maps/map1.cub

map2: all
	@./$(NAME) maps/map2.ber

map3: all
	@./$(NAME) maps/map3.ber