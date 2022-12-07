# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 13:20:07 by aestraic          #+#    #+#              #
#    Updated: 2022/11/22 16:59:16 by aestraic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =  	ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c\
ft_isprint.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strlcat.c ft_strlcpy.c\
ft_strlen.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c\
ft_memchr.c ft_memcmp.c  ft_atoi.c ft_calloc.c ft_strdup.c ft_strnstr.c\
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c\
ft_strjoin.c ft_substr.c ft_itoa.c ft_striteri.c ft_strtrim.c ft_strmapi.c\
ft_lstnew.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c\
ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstsize.c

COMPILED = $(SRC:.c=.o)

HEADER_PATH = ../../header
LIB_PATH = ../../lib
OBJ_PATH = ../../obj

all: $(NAME)

%.o : %.c 
	cc -g -Wall -Wextra -Werror -I $(HEADER_PATH) -c $^

$(NAME): $(COMPILED)
	@ar -rucv $(LIB_PATH)/$(NAME) $^

move:
	@mv $(COMPILED)$^ $(OBJ_PATH)

clean:
	@rm -f $(COMPILED)

fclean: clean
	@rm -f $(LIB_PATH)/$(NAME)
	
re: fclean $(NAME)

.PHONY: clean fclean re