NAME	= pipex

NAME_BONUS = pipex_bonus.x

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRCS	= utils.c

SRCS_MAIN	= pipex.c $(SRCS)

SRCS_BONUS	= utils_bonus.c

MAIN_BONUS	= pipex_bonus.c $(SRCS_BONUS)

OBJS	= $(SRCS_MAIN:.c=.o)

OBJS_BONUS	= $(MAIN_BONUS:.c=.o)

CC	= @gcc

CFLAGS	+= -Wall -Wextra -Werror -g3 #-fsanitize=address

RM	= @rm -rf

all	: $(NAME)

bonus	: $(NAME_BONUS)

$(NAME) : $(OBJS)
	@make --no-print-directory -C Libft
	$(CC) $(CFLAGS) $(OBJS) Libft/libft.a -o $(NAME)
	@echo "$(MAGENTA)Make Done$(DEF_COLOR)"

$(NAME_BONUS) : $(OBJS_BONUS)
	@make --no-print-directory -C Libft
	$(CC) $(CFLAGS) $(OBJS_BONUS) Libft/libft.a -o $(NAME_BONUS)
	@echo "$(YELLOW)Make Bonus Done$(DEF_COLOR)"

clean : 
	$(RM) $(OBJS) $(OBJS_BONUS)
	@make --no-print-directory -C Libft clean
	@echo "$(BLUE)OBJS CLEAR MY FRIEND!$(DEF_COLOR)"

fclean : 
	$(RM) $(NAME) $(OBJS) $(NAME_BONUS) $(OBJS_BONUS)
	@make --no-print-directory -C Libft fclean
	@echo "$(MAGENTA)¯|_(ツ)_/¯ I'M SO PROUD OF U!$(DEF_COLOR)"


re :	fclean all bonus

ex :	re clean
	@echo "$(GREEN)(•̀ᴗ•́)و ̑̑ALL FINE!(•̀ᴗ•́)و ̑̑$(DEF_COLOR)"