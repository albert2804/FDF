# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 13:20:07 by aestraic          #+#    #+#              #
#    Updated: 2022/11/22 11:56:40 by aestraic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = 	ft_conv_character.c\
		ft_conv_hex1.c\
		ft_conv_int.c\
		ft_conv_pointer.c\
		ft_conv_str.c\
		ft_conv_unsigned.c\
		ft_printf.c

COMPILED = $(SRC:.c=.o)

HEADER_PATH = ../../header
LIB_PATH = ../../lib
OBJ_PATH = ../../obj


all: $(NAME)
		
%.o: %.c
	cc -g -Wall -Wextra -Werror -I $(HEADER_PATH) -c $^

$(NAME):$(COMPILED)
	@ar -rucv $(LIB_PATH)/$(NAME) $^

move:
	@mv $(COMPILED)$^ $(OBJ_PATH)

clean:
	@rm -f $(COMPILED)
 
fclean: clean
	@rm -f $(LIB_PATH)/$(NAME)
 
re: fclean $(NAME)

.PHONY: clean fclean re