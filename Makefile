# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 00:22:02 by maheraul          #+#    #+#              #
#    Updated: 2023/07/01 00:28:27 by maheraul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

LIBFT			=	libft.a

PRINTF			=	libftprintf.a

SRCS			=	srcs/main.c \
					srcs/utils.c \
					srcs/pipex.c \
					srcs/redirection.c \
					srcs/parse_input.c \
					srcs/lst.c \
					srcs/fill_cmd_struct.c

OBJS			=	${SRCS:.c=.o}

HEAD			=	-Iincludes -lreadline

CC				=	cc

CFLAGS			=	-Iincludes -Ilibs/ft_printf -Ilibs/libft -g3 -Wall -Werror -Wextra

all				:	${NAME}

bonus			: ${NAME_BONUS}

$(NAME): $(OBJS)
	@make -C libs/libft
	@make -C libs/ft_printf
	@mv libs/libft/libft.a .
	@mv libs/ft_printf/libftprintf.a .
	cc $(HEAD) $(OBJS) ${LIBFT} ${PRINTF} -o $(NAME)

clean			:
					make clean -C libs/libft
					make clean -C libs/ft_printf
					rm -rf ${OBJS} ${OBJS_BONUS}

fclean			:	clean
					make fclean -C libs/libft
					make fclean -C libs/ft_printf
					rm -rf ${LIBFT}
					rm -rf ${PRINTF}
					rm -rf ${NAME}

re				:	fclean all

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.txt  --track-fds=yes    ./minishell

.PHONY			:	all clean fclean re bonus
