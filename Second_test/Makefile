# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 14:33:20 by root              #+#    #+#              #
#    Updated: 2025/02/15 22:26:23 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = philo

# Compilateur et options
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

# Fichiers source pour so_long
SRCS = main.c \
		philo_utils.c \
		utils/initialize_philo.c \
		utils/parsing.c \
		utils/actions.c \
		print_status.c \

# Objets
OBJS = $(SRCS:.c=.o)

# Cibles
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Règle pour compiler les fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cible de nettoyage
clean:
	$(RM) $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re