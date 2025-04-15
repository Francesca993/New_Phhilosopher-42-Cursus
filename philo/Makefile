# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francesca <francesca@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 14:23:25 by francesca         #+#    #+#              #
#    Updated: 2025/04/11 14:44:26 by francesca        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
BLUE		=	\033[0;34m
RESET		=	\033[0m

NAME	=	philo

CC		=	clang
# compilation flags
CFLAGS	=  -Wall -Werror -Wextra -pthread -g

SRCS_DIR	=	src/
OBJS_DIR	=	obj/

SRCS	=	philosophers.c \
			ft_atoi.c \
			ft_free_all.c \
			ft_check_args.c \
			ft_init.c \
			ft_routine.c \
			ft_action_utils.c \
			ft_action.c \

SRCS := $(addprefix $(SRCS_DIR), $(SRCS))
OBJS := $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

all:	$(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking objects and creating $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@echo "$(RED)Cleaning object files...$(RESET)"
				@$(RM) -r $(OBJS_DIR)

fclean:			clean
				@echo "$(RED)Removing executable...$(RESET)"
				@$(RM) $(NAME)

re:				fclean all 

norm:
				@echo "$(BLUE)Running norminette...$(RESET)"
				@norminette $(SRCS) $(SRCS_DIR)philo.h
	
.PHONY : all bonus clean fclean re