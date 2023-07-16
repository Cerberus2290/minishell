NAME			=	minishell

CC				=	cc

CFLAGS			=	-g -Wall -Wextra -Werror #-fsanitize=address

RM				=	rm -rf

#colors
DEF_COLOR		=	\033[0;39m
ORANGE			=	\033[0;33m
GREY			=	\033[0;90m
RED				=	\033[0;91m
GREEN			=	\033[1;92m
YELLOW			=	\033[1;93m
BLUE			=	\033[0;94m
MAGENTA			=	\033[0;95m
CYAN			=	\033[0;96m
WHITE			=	\033[0;97m

LIBFT			=	-L libft -lft

HEADER			=	minishell.h

BUILTINS		=	builtin_util cmd_cd cmd_echo cmd_env cmd_exit cmd_export cmd_pwd cmd_unset

DIRECTIONS		=	direction_heredoc direction_input direction_output directions_util

ENVIRO			=	envi_str_util enviro enviro_util

EXECUTE			=	execute_bin execute_builtins execute_cmd execute_cmd_util execute_cmds execute_cmds_util \
					find_path pipes split_args wait_signal

EXPANSION		=	expand_exit_ret expand_vars expand_vars_util

MAIN			=	handle_heredoc input_error main minishell prompt split_cmds

SYNTAX_CHECK	=	syntax_check syntax_utils

UTIL			=	array_free array_len error_msg fds ft_atoll label_name quotes signal_handler \
					str_checker str_utils

SRCS			=	$(addsuffix .c, $(addprefix src/builtins/, $(BUILTINS))) \
					$(addsuffix .c, $(addprefix src/directions/, $(DIRECTIONS))) \
					$(addsuffix .c, $(addprefix src/enviro/, $(ENVIRO))) \
					$(addsuffix .c, $(addprefix src/execute/, $(EXECUTE))) \
					$(addsuffix .c, $(addprefix src/expansion/, $(EXPANSION))) \
					$(addsuffix .c, $(addprefix src/main/, $(MAIN))) \
					$(addsuffix .c, $(addprefix src/syntax_check/, $(SYNTAX_CHECK))) \
					$(addsuffix .c, $(addprefix src/util/, $(UTIL))) \

OBJS			=	$(SRCS:c=o)

all:			$(NAME)
				@echo "$(CYAN)********************************************"
				@echo "*          To check Norminette             *"
				@echo "*            type: $(WHITE)make norm$(CYAN)               *"
				@echo "********************************************$(DEF_COLOR)"
				@echo
				@echo "$(GREEN)*********************************************"
				@echo "*           To run minishell                *"
				@echo "*           type: $(WHITE)./minishell$(GREEN)               *"
				@echo "* $(GREY)hint: try giving minishell an argument ;)$(GREEN) *"
				@echo "*********************************************$(DEF_COLOR)"
				@read -p "Press ENTER to continue"

$(NAME):		$(OBJS)
				@echo "\n"
				@make -C libft/
				@echo "$(YELLOW)Compiling minishell...$(DEF_COLOR)"
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline -I/Users/tstrassb/.brew/Cellar/readline/8.2.1/include -L/Users/tstrassb/.brew/Cellar/readline/8.2.1/lib $(LIBFT)
				@echo "$(GREEN)minishell ready!$(DEF_COLOR)"

%.o:			%.c
					@printf "$(BLUE)creating minishell objects... %-33.33s\r" $@
					@$(CC) ${CFLAGS} -c $< -I/Users/tstrassb/.brew/Cellar/readline/8.2.1/include -o $@

norm:
				@echo "$(CYAN)Checking the Norm..."
				@sleep 1
				@norminette src/ incl/
				@echo "$(DEF_COLOR)"

clean:
				@echo "Cleaning..."
				@make clean -C libft/
				@rm -f $(OBJS)
				@echo "Done!"

fclean:
				@echo "Cleaning all..."
				@make fclean -C libft/
				@rm -f $(OBJS)
				@rm -f $(NAME)
				@rm -rf minishell.dSYM
				@echo "Done!"

re:				fclean all