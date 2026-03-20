# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpiasecz <mpiasecz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/23 11:12:09 by mpiasecz          #+#    #+#              #
#    Updated: 2025/12/27 12:29:08 by mpiasecz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

PARSING_DIR = parsing
UTILS_DIR = utils
MUTEX_DIR = mutex
PHILO_DIR = philosophers

SRCS = main.c $(PARSING_DIR)/parsing.c $(UTILS_DIR)/get_time.c $(UTILS_DIR)/ft_atol.c $(UTILS_DIR)/cleanup.c $(UTILS_DIR)/philo_utils.c $(MUTEX_DIR)/mutex_init.c $(PHILO_DIR)/monitor.c $(PHILO_DIR)/create_philos.c $(PHILO_DIR)/routine.c

OBJS := $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJS))
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

HEADERS = $(INC_DIR)/philo.h

INCLUDES = -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
