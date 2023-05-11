# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhirch <mhirch@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 18:49:14 by mhirch            #+#    #+#              #
#    Updated: 2023/05/11 16:32:59 by mhirch           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGRAM_NAME = so_long


HEADER = so_long.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

FILES = so_long.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	check.c check_utils.c libft.c moves.c mlx_utils.c utils.c path.c 

OBJ = $(FILES:.c=.o)


all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJ) $(HEADER)
	$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(PROGRAM_NAME)
	
%.o: %.c $(HEADER) $(BONUS_HEADER)
	$(CC) -Imlx $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(PROGRAM_NAME) $(CHECKER_NAME)

re: fclean all

.PHONY: all clean fclean re