# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 14:30:19 by pamatya           #+#    #+#              #
#    Updated: 2024/05/03 14:09:21 by pamatya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

NAME	=	gnl.a
FTDIR	=	Libft
FT		=	libft.a
UTIL	=	./Utilities

SRCS	=	get_next_line.c get_next_line_utils.c
OBJS	=	$(SRCS:.c=.o)

CURRENT	=	test_main

all: $(NAME)

# $(NAME): $(OBJS) $(FT)
# 	cp ./$(FTDIR)/$(FT) ./$(NAME)
# 	ar rcs $(NAME) $(OBJS)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# $(FT):
# 	$(MAKE) -C $(FTDIR) all

clean:
	$(RM) $(OBJS)
# $(MAKE) -C $(FTDIR) clean

fclean: clean
	$(RM) $(NAME)
# $(MAKE) -C $(FTDIR) fclean

re: fclean all



lib: re
	$(MAKE) clean

now:
	$(CC) $(CFLAGS) $(NAME) $(CURRENT).c -o $(CURRENT)
	./$(CURRENT) | tr -d '\r' | cat -e

both: lib now

clr: fclean
	$(RM) $(CURRENT).o
	$(RM) $(CURRENT)



.PHONY: all clean fclean re lib now both clr
