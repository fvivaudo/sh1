# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvivaudo <fvivaudo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/07/16 09:42:25 by fvivaudo          #+#    #+#              #
#    Updated: 2015/03/13 11:00:00 by fvivaudo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Werror -Wextra

SRC = 	srcs/ft_builtin.c	\
		srcs/ft_cd.c		\
		srcs/ft_env.c		\
		srcs/ft_env2.c		\
		srcs/ft_sh1.c		\
		srcs/ft_sig.c



OBJ  = $(subst srcs/,,$(SRC:.c=.o))

NAME = ft_minishell

all : $(NAME)

$(NAME) :
	@make -C libft
	@gcc $(FLAGS) $(SRC) -I includes/ -I libft/includes -L libft/ -lft -o $(NAME)

clean:
	@rm -Rf $(OBJ)

fclean: clean
	@rm -Rf $(NAME)

re: fclean all
	
