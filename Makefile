# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 13:20:07 by aestraic          #+#    #+#              #
#    Updated: 2022/12/13 12:49:45 by aestraic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = 	main.c\
		utils1.c\
		read.c

SRC_TEST = 	test.c\
			read.c\
			utils1.c\
			parallel_proj.c\
			hooks.c\
			colors.c\
			draw.c

OBJ   = $(SRC:.c=.o)
INPUT = 42.fdf

HEADER_PATH = header
LIB_PATH = lib
SRC_PATH = src
OBJ_PATH = obj
C_FLAGS = -Wall -Wextra -Werror
LIB_MLX = ./mlx/libmlx42.a -lglfw  -L ~/.brew/opt/glfw/lib\
	-framework Cocoa -framework OpenGL -framework IOKit

all:   library obj $(NAME)

test: 
	make library
	cc $(C_FLAGS) -g -Ofast -o test $(SRC_TEST) $(LIB_MLX) -I$(HEADER_PATH) -Llib -lft 

obj: $(OBJ)

%.o : %.c
	cc $(C_FLAGS) -I$(HEADER_PATH) -c $^
	
$(NAME): $(OBJ)
	cc $(C_FLAGS) $(LIB_MLX) -I$(HEADER_PATH) $(OBJ) -L$(LIB_PATH) -lft -o $(NAME)

library:
#	@echo MAKE LIBFT
	@make all -C	$(SRC_PATH)/libft
	
#	@echo MAKE PRINTF
	@make all -C	$(SRC_PATH)/ft_printf

#	@echo MAKE GNL	
	@make all -C	$(SRC_PATH)/gnl
	
val:
	make library && make test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test $(INPUT)

move:
	@make move -C	$(SRC_PATH)/libft
	@make move -C	$(SRC_PATH)/ft_printf
	@mv $(OBJ)$^ $(OBJ_PATH)
	@echo Moved Objectfiles into /$(OBJ_PATH)

clean:
	@rm -f $(OBJ) $(NAME)
	@echo Objectfiles removed

fclean: clean
	@make fclean -C $(SRC_PATH)/libft
	@make fclean -C $(SRC_PATH)/ft_printf
	@make fclean -C $(SRC_PATH)/gnl
	@rm -f $(NAME)
	@echo Libraries and exeutables removed
	
re: fclean all
	@echo REDONE

.PHONY: clean fclean re obj exec library test