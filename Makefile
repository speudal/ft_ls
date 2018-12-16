# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tduval <tduval@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/11 14:45:40 by tduval            #+#    #+#              #
#    Updated: 2018/12/16 05:06:56 by tduval           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

INCLUDES	=	-I . -I libft

LIBFT		=	libft/libft.a

NAME		=	ft_ls

OBJ			=	$(SRC:.c=.o)

SRC			=	main.c					\
				print_l/print_l.c		\
				print_l/get_padding.c	\
				hubs/hub_files.c		\
				hubs/hub_dirs.c			\
				print_br/print_br.c		\
				sorts/sort_alpha.c		\
				sorts/sort_time.c		\
				sorts/sort_reverse.c	\
				srcs/inf_new.c			\
				srcs/utils.c			\
				srcs/get_files.c		\
				srcs/get_dirs.c			\
				srcs/get_opts.c	


all: $(NAME)

$(NAME) : $(OBJ)
	@$(MAKE) -C libft
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\x1b[36m[FT_LS COMPILED]\x1b[0m"

%.o : %.c
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean :
	@echo "\x1b[33;01mft_ls : cleaning...\x1b[0m"
	@echo "\x1b[32;01m[FT_LS CLEANED]\x1b[0m"
	@$(MAKE) -C libft clean
	@rm -f $(OBJ)

fclean : clean
	@$(MAKE) -C libft fclean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
