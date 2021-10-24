# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/11 18:23:16 by ael-azra          #+#    #+#              #
#    Updated: 2021/10/24 13:53:36 by ael-azra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	./file/main.c \
		./file/read_input.c \
		./file/libft.c \

FLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc $(FLAG) $(SRC) -o $(NAME)

clean:
	@echo "Nothing to clean!"

fclean:
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re