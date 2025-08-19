# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpaes-so <dpaes-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 17:23:52 by dpaes-so          #+#    #+#              #
#    Updated: 2025/05/20 17:32:30 by dpaes-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

CC = cc
FLAGS = -Wall -Werror -Wextra -g

SRC_FILES =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
		ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
		ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
		ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c get_next_line.c get_next_line_utils.c \
		ft_strcmp.c ft_freetrix.c  ft_atol.c ft_matrix_dup.c ft_matrix_sort.c

PRINTF = $(addprefix ./printf/, ft_putcharf.c  ft_putnbrbasef.c  ft_putnbrf.c ft_putnbrf_unsigned.c \
		ft_putstrf.c  ft_putptr.c ft_printf.c)
DPRINTF = $(addprefix ./dprintf/, ft_fdputcharf.c  ft_fdputnbrbasef.c  ft_fdputnbrf.c ft_fdputnbrf_unsigned.c \
		ft_fdputstrf.c  ft_fdputptr.c ft_fdprintf.c)

BONUS_FILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUS_OBJS = $(BONUS_FILES:.c=.o)
OBJS = $(SRC_FILES:.c=.o)
PRINTF_OBJ = $(PRINTF:.c=.o)
DPRINTF_OBJ = $(DPRINTF:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS) $(PRINTF_OBJ) $(DPRINTF_OBJ)
	@ar rcs $(NAME) $(OBJS) $(PRINTF_OBJ) $(DPRINTF_OBJ)

bonus: $(BONUS_OBJS) $(NAME)
	@ar rcs $(NAME) $(BONUS_OBJS)
	
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(PRINTF_OBJ): %.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

$(DPRINTF_OBJ): %.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	
clean:
	@rm -f $(OBJS)
	@rm -f $(BONUS_OBJS)
	@rm -f $(PRINTF_OBJ)
	@rm -f $(DPRINTF_OBJ)
fclean: clean
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all fclean clean re