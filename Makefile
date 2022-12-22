# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 13:20:07 by aestraic          #+#    #+#              #
#    Updated: 2022/12/22 15:50:46 by aestraic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC = 	main.c\
		read.c\
		utils.c\
		bresenham.c\
		parallel_proj.c\
		input.c\
		hooks.c\
		colors.c\
		draw.c

OBJ  = $(SRC:.c=.o)

C_FLAGS = -Wall -Wextra -Werror
HEADER_PATH = header
SRC_PATH = src
OBJ_PATH = obj
LIB_PATH = lib
MAP_PATH = test_maps
LIB = $(LIB_PATH)/libft.a
LIB_MLX = ./$(MAKE_MLX) -lglfw  -L $(INST_GLFW)\
	-framework Cocoa -framework OpenGL -framework IOKit

MLX_DIR = MLX42/
MAKE_MLX = $(MLX_DIR)libmlx42.a
INST_GLFW = /Users/$(USER)/.brew/opt/glfw/lib/
INST_BREW = /Users/$(USER)/.brewconfig.zsh

all: $(NAME)

%.o : %.c
	gcc $(C_FLAGS) -I$(HEADER_PATH) -c $^
	
$(NAME): $(INST_BREW) $(INST_GLFW) $(MAKE_MLX) $(LIB) $(OBJ) $(MAP_PATH)
	gcc $(C_FLAGS) -Ofast -o $(NAME) $(SRC) $(LIB_MLX) -I$(HEADER_PATH) -Llib -lft 

$(LIB):
	@mkdir -p $(LIB_PATH)
	@make all -C	$(SRC_PATH)/libft
	@make all -C	$(SRC_PATH)/ft_printf
	@make all -C	$(SRC_PATH)/gnl

$(MAKE_MLX): $(MLX_DIR)
	make -C $(MLX_DIR)
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
	@curl -fsSL https://projects.intra.42.fr/uploads/document/document/9222/maps.zip | tar -xz 
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
	@-make fclean -C $(MLX_DIR)
	@rm -f $(NAME) $(BONUS)
	@echo Libraries and exeutables removed
	
re: fclean all
	@echo REDONE

.PHONY: clean fclean re all bonus val

https://projects.intra.42.fr/uploads/document/document/9222/maps.zip