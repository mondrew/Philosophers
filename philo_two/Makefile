# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mondrew <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 11:10:37 by mondrew           #+#    #+#              #
#    Updated: 2020/11/26 22:39:32 by mondrew          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two
SRCS = 	./srcs/ft_utils.c \
		./srcs/main.c \
		./srcs/ft_operate_and_print.c \
		./srcs/ft_philo_life.c \
		./srcs/ft_isdigit.c \
		./srcs/ft_atoi.c \
		./srcs/ft_itoa.c \
		./srcs/ft_putchar.c \
		./srcs/ft_putstr.c \
		./srcs/ft_strlen.c \
		./srcs/ft_additional.c \
		./srcs/ft_init_destroy_semaphores.c \
		./srcs/ft_monitor.c \
		./srcs/ft_mute_if_greedy.c

INCLUDES = ./includes
FLAGS = -Wall -Wextra -Werror
PTHREAD = -pthread
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

%.o: %.c
	@gcc $(FLAGS) $(PTHREAD) -I $(INCLUDES) -c $< -o $@
	@echo "Compiling... Please wait..."

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling ... Please wait..."
	@gcc $(OBJS) $(PTHREAD) -o $(NAME)
	@echo "Compilation successfully done!"

clean:
	@echo "Cleaning object files ..."
	@/bin/rm -f $(OBJS)
	@echo "Object files has been removed!"

fclean: clean
	@echo "Cleaning all ..."
	@/bin/rm -f $(NAME)
	@echo "Everything has been removed!"

re: fclean all
