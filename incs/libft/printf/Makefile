# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 12:46:52 by dpaes-so          #+#    #+#              #
#    Updated: 2024/11/04 14:03:09 by dpaes-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = cc
FLAGS = -Wall -Werror -Wextra

SRC_FILES = ft_putcharf.c  ft_putnbrbasef.c  ft_putnbrf.c ft_putnbrf_unsigned.c \
		ft_putstrf.c  ft_putptr.c ft_printf.c

OBJS = $(SRC_FILES:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all fclean clean re