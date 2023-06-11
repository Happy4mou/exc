NAME = minishell
LIBFT = libft/libft.a
CFLAGS = -Wall -Wextra -Werror   #-fsanitize=address -g3 
RM = rm -f
SRC = 	minishell.c \
		exc/env.c\
		exc/heredoc.c\
		exc/exc.c\
		exc/exit.c\
		exc/export.c\
		exc/getnextline/get_next_line.c\
		exc/getnextline/get_next_line_utils.c\
		exc/echo.c\
		exc/cd.c\
		exc/unset.c\
		exc/pipe_and_cmd.c\
		exc/one_cmd.c\
		exc/open_files.c\
		parcing/p_str_to_nbr.c \
		parcing/p_split_pro.c \
		parcing/p_fill_lst.c \
		parcing/p_linked_list.c \
		parcing/p_free_all.c \
		parcing/p_fill_lst_count.c \
		parcing/p_remove_cout.c \
		parcing/p_fill_env_list.c\
		parcing/p_expand.c\
		parcing/p_syntax_error.c\

OBJ = $(SRC:.c=.o)

all: $(NAME) $(LIBFT)

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS)  -lreadline  $(SRC) $(LIBFT) -o $(NAME) 

$(LIBFT):
	@make all clean -C libft

clean:
	$(RM) $(OBJ)
	@make clean -C libft 

fclean: clean
	$(RM) $(NAME)
	@make fclean -C libft 

re: fclean all 

# -fsanitize=address -fsanitize=undefined -fsanitize=null -g3 