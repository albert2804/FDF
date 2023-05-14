# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 13:20:07 by aestraic          #+#    #+#              #
#    Updated: 2023/05/14 15:10:42 by aestraic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## INSTALL MLX
## After the MLX42 directory is downloaded,
## - cd MLX42
## - mkdir build
## - cd build
## cmake && make, so that the libmlx42.a is produced.

NAME = fdf
SRC = 	main.c\
		read.c\
		utils1.c\
		utils2.c\
		bresenham.c\
		parallel_proj.c\
		input.c\
		hooks.c\
		colors.c\
		mem1.c\
		mem2.c\
		draw.c

OBJ  = $(SRC:.c=.o)

C_FLAGS = -Wall -Wextra -Werror
HEADER_PATH = header
SRC_PATH = src
OBJ_PATH = obj
LIB_PATH = lib
MAP_PATH = test_maps
LIB = $(LIB_PATH)/libft.a
LIB_MLX = ./$(MAKE_MLX_LIB) -lglfw  -L $(INST_GLFW)\
	-framework Cocoa -framework OpenGL -framework IOKit

MLX_DIR = MLX42/
MAKE_MLX_LIB = $(MLX_DIR)build/libmlx42.a
INST_GLFW = /Users/$(USER)/.brew/opt/glfw/lib/
INST_BREW = /Users/$(USER)/.brewconfig.zsh

all: $(NAME)

%.o : %.c
	gcc $(C_FLAGS) -I$(HEADER_PATH) -c $^
	
$(NAME): $(INST_BREW) $(INST_GLFW) $(MAKE_MLX_LIB) $(LIB) $(OBJ) $(MAP_PATH)
	gcc $(C_FLAGS) -Ofast -o $(NAME) $(SRC) $(LIB_MLX) -I$(HEADER_PATH) -Llib -lft 

$(LIB):
	@mkdir -p $(LIB_PATH)
	@make all -C	$(SRC_PATH)/libft
	@make all -C	$(SRC_PATH)/ft_printf
	@make all -C	$(SRC_PATH)/gnl

$(MAKE_MLX_LIB): $(MLX_DIR)
	@mkdir -p $(MLX_DIR)build		
	@cmake -B $(MLX_DIR)build $(MLX_DIR)
#cmake -B<path-to-build> -S<path-to-source(CMakeLists.txt)>
	@make -C $(MLX_DIR)build
$(MLX_DIR):
	@echo Cloning MLX42
	git clone https://github.com/codam-coding-college/MLX42.git
$(INST_GLFW):
	@echo Installing GLFW
		brew install glfw
$(INST_BREW):
	@echo Installing Brew
	@curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	@source ~/.zshrc
$(MAP_PATH):
	@curl -fsSL https://cdn.intra.42.fr/document/document/13499/maps.zip | tar -xz 
	@rm -rf __MACOSX

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

clean:
	@rm -f $(OBJ) $(OBJ_B)
	@make clean -C $(SRC_PATH)/libft
	@make clean -C $(SRC_PATH)/ft_printf
	@make clean -C $(SRC_PATH)/gnl
	@echo Objectfiles removed

fclean: clean
	@make fclean -C $(SRC_PATH)/libft
	@make fclean -C $(SRC_PATH)/ft_printf
	@make fclean -C $(SRC_PATH)/gnl
	@rm -f $(NAME) $(BONUS)
	@echo Libraries and exeutables removed

aclean: fclean
	@rm -rf test_maps
	@rm -rf MLX42
	@echo Maps and MLX removed
	
re: fclean all
	@echo REDONE

.PHONY: clean fclean aclean re all bonus val
