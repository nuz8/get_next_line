# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 14:30:19 by pamatya           #+#    #+#              #
#    Updated: 2024/05/08 14:43:17 by pamatya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
# CFLAGS	=	-Wall -Wextra -Werror
CFLAGS	=	-Wall -Wextra -Werror -D BUFFER_SIZE=42
RM		=	rm -f

NAME	=	gnl.a
BONUS	=	gnl_bonus.a
FTDIR	=	Libft
FT		=	libft.a
UTIL	=	./Utilities

SRCS	=	get_next_line.c get_next_line_utils.c
SRC_BON	=	get_next_line_bonus.c get_next_line_utils_bonus.c
OBJS	=	$(SRCS:.c=.o)
OBJ_BON	=	$(SRC_BON:.c=.o)

CURRENT	=	test_main
BUG		=	bug

all: $(NAME)
	@echo ">>Executed make all"

# $(NAME): $(OBJS)
# 	@cp ./$(FTDIR)/$(FT) ./$(NAME)
# 	@ar rcs $(NAME) $(OBJS)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

# $(NAME): $(OBJS) $(FT)
# 	ar rcs $(NAME) $(OBJS)

# $(FT):
# 	$(MAKE) -C $(FTDIR) all

bonus: $(BONUS)
	@echo ">>Executed make all"
	$(CC) $(CFLAGS) $(BONUS) $(CURRENT).c -o $(CURRENT)_bonus
	@./$(CURRENT)_bonus

$(BONUS): $(OBJ_BON)
	@ar rcs $(BONUS) $(OBJ_BON)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJ_BON)

# $(MAKE) -C $(FTDIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS)
	
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
	$(RM) $(CURRENT)_bonus
	$(RM) $(BUG)
	$(RM) a.out
	$(RM) -R ./*.dSYM

clb:
	$(RM) $(BUG)

bug: clb
	$(CC) $(CFLAGS) $(CURRENT).c $(SRCS) ./$(FTDIR)/$(FT) -o $(BUG) -g


.PHONY: all clean fclean re lib now both clr clb bug
