NAME		= pipex
CC			= clang
FLAGS		= -g3 -Wall -Wextra -Werror
RM			= rm -rf

SRCS		= pipex.c \
			execution.c
HEADER		= pipex.h
OBJS		= $(SRCS:.c=.o)

LIBFT_D		= libft/
LIBFT		= $(LIBFT_D)libft.a

all:		library	$(NAME)

$(NAME):	$(LIBFT) COMP $(OBJS) DONE
			@$(CC) $(FLAGS) $(LIBFT) $(OBJS) -o $(NAME)
		
%.o:		%.c
			$(CC) -c $(FLAGS) -o $@ $<
			printf "$(CYAN)...."

library:	
			@$(MAKE) -C $(LIBFT_D)

clean:		CLEAN
			@$(RM) $(OBJS)
			@$(MAKE) -C $(LIBFT_D) clean

fclean:		clean FCLEAN
			@$(RM) $(NAME)
			@$(RM) $(LIBFT)

re:			fclean all

leaks:
			valgrind --leak-check=full --show-leak-kinds=definite ./$(NAME) infile "ls -la" "grep Make" outfile

git:		
			make fclean
			git add .
			git commit -m "commit"
			git push

space:		SPACE
			@$(RM) ~/Library/Caches/*
			@$(RM) ~/Library/*42_cache*
			@$(RM) ~/Library/Application\ Support/Slack/Service\ Worker/CacheStorage/
			@$(RM) ~/Library/Application\ Support/Slack/Cache/
			@$(RM) ~/Library/Application\ Support/Slack/Code\ Cache/
			@$(RM) ~/Library/Application\ Support/Code/Cache/*
			@$(RM) ~/Library/Application\ Support/Code/CachedData/*
			@$(RM) ~/Library/Application Support/Spotify/PersistentCache
			@$(RM) ~/Library/Application\ Support/Code/User/workspaceStorage

.PHONY:		all clean fclean re
.SILENT:

COMP:
	echo "$(CYAN) COMPILING $(NAME) $(DEFAULT)\n"
DONE:
	echo "$(GREEN)\n\n $(NAME) COMPILED $(DEFAULT)\n"
CLEAN:
	echo "\n$(YELLOW) REMOVING OBJECT FILES $(DEFAULT)"
FCLEAN:
	echo "$(RED) REMOVING EXECUTABLE AND LIBRARY $(DEFAULT)"
SPACE:
	echo "$(BLUE) CACHES CLEARED $(DEFAULT)"

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
WHITE = \033[1;37m
BLUE = \033[1;34m
PURPLE = \033[1;35m
DEFAULT = \033[0m