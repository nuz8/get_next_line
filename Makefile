# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 14:30:19 by pamatya           #+#    #+#              #
#    Updated: 2024/05/05 23:53:00 by pamatya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
# CFLAGS	=	-Wall -Wextra -Werror
CFLAGS	=	-Wall -Wextra -Werror -D BUFFER_SIZE=42
RM		=	rm -f

NAME	=	gnl.a
FTDIR	=	Libft
FT		=	libft.a
UTIL	=	./Utilities

SRCS	=	get_next_line.c get_next_line_utils.c
OBJS	=	$(SRCS:.c=.o)

CURRENT	=	test_main
BUG		=	bug

all: $(NAME)
	@echo ">>Executed make all"

# $(NAME): $(OBJS)
# 	@cp ./$(FTDIR)/$(FT) ./$(NAME)
# 	@ar rcs $(NAME) $(OBJS)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

# $(NAME): $(OBJS)
# 	ar rcs $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# $(FT):
# 	$(MAKE) -C $(FTDIR) all

clean:
	@$(RM) $(OBJS)

# $(MAKE) -C $(FTDIR) clean

fclean: clean
	@$(RM) $(NAME)
	
# $(MAKE) -C $(FTDIR) fclean

re: fclean all



lib: re
	@$(MAKE) clean

now:
	$(CC) $(CFLAGS) $(NAME) $(CURRENT).c -o $(CURRENT)
	@./$(CURRENT)

both: lib now

clr: fclean
	$(RM) $(CURRENT).o
	$(RM) $(CURRENT)
	$(RM) $(BUG)
	$(RM) a.out
	$(RM) -R ./*.dSYM

clb:
	$(RM) $(BUG)

bug: clb
	$(CC) $(CFLAGS) $(CURRENT).c $(SRCS) ./$(FTDIR)/$(FT) -o $(BUG) -g


.PHONY: all clean fclean re lib now both clr clb bug
