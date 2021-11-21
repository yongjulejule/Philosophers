# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 20:27:28 by yongjule          #+#    #+#              #
#    Updated: 2021/11/21 14:41:05 by yongjule         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc

ifdef DEBUG
	CFLAGS = -g3 -fsanitize=address
else ifdef LEAKS
	CFLAGS = -g
else 
	CFLAGS = -Wall -Wextra -Werror
endif

NAME			=	philo

SRCS_DIR		=	src/

INC_DIR			=	include/

SRCS			=	$(addprefix $(SRCS_DIR), \
					check_validity.c\
					ft_utils.c\
					get_info.c\
					handle_error.c\
					main.c\
					gen_philosophers.c\
					free_structure.c\
					sleep_and_think.c\
					eat.c\
				)

OBJS			=	${SRCS:%.c=%.o}

######################### Color #########################
GREEN="\033[32m"
L_GREEN="\033[1;32m"
YELLOW="\033[33m"
RED="\033[31m"
L_RED="\033[1;31m"
BLUE="\033[34m"
L_BLUE="\033[1;34m"
MUTED="\033[130m"
RESET="\033[0m"
BOLD="\033[1m"
L_PUPLE="\033[1;35m"
UP = "\033[A"
DOWN = "\033[B"
RIGHT = "\033[C"
LEFT = "\033[D"
CUT = "\033[K"
SAVE = "\033[s"
RESTORE = "\033[u"

########################## Rule ##########################

.PHONY			:	all
all				:	$(OBJS) $(NAME)

$(NAME)			: 	$(OBJS)
					@$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) -o $@ 
					@printf $(CUT)$(DOWN)$(CUT)
					@echo $(CUT)$(UP)$(BOLD)$(L_PUPLE)🎉 Philosophers Compiled !! 🎉$(RESET)

%.o				: 	%.c
					@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
					@echo $(CUT)$(BOLD)$(L_GREEN) Compiling with $(CFLAGS)...$(RESET)
					@echo $(CUT)$(GREEN) [$(notdir $^)] to [$(notdir $@)] $(RESET)
					@printf $(UP)$(UP)


.PHONY			:	clean
clean			:
					@rm -f $(OBJS)
					@echo $(L_RED) Remove🧹 OBJ files in philosophers 👋 $(RESET)


.PHONY			:	fclean
fclean			:	clean
					@rm -f $(NAME)
					@echo $(RED) Remove🧹 $(NAME)🦪 $(RESET)

.PHONY			:	re
re				:	fclean all

.PHONY			:	debug
debug			: 
					@make DEBUG=1
					@echo $(CUT)$(RED)$(BOLD) It\'s DEBUG TIME🤪$(RESET)

leaks			:
					@make LEAKS=1
					@echo $(CUT)$(RED)$(BOLD) Is there Leaks?🚰$(RESET)