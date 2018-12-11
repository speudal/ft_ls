# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tduval <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/11 14:45:40 by tduval            #+#    #+#              #
#    Updated: 2018/12/11 21:54:41 by tduval           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

CFLAGS		=	#-Wall -Werror -Wextra

INCLUDES	=	-I . -I libft

LIBFT		=	libft/libft.a

NAME		=	ft_ls

SRC			=	main.c					\
				srcs/widthn.c			\
				srcs/sorts.c			\
				print/print_files.c		\
				print/print_l.c			\
				srcs/get_files.c		\
				srcs/get_dirs.c			\
				srcs/get_opts.c	

OBJ			=	$(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	@$(MAKE) -C libft
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\x1b[36m[FT_LS COMPILED]\x1b[0m"

clean :
	@echo "\x1b[33;01mft_ls : cleaning...\x1b[0m"
	@echo "\x1b[32;01m[FT_LS CLEANED]\x1b[0m"
	@$(MAKE) -C libft clean
	@rm -f $(OBJ)

fclean : clean
	@$(MAKE) -C libft fclean
	@rm -f $(NAME)

%.o : %.c
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

re : fclean all

.PHONY : all clean fclean re
