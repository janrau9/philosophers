# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 11:38:23 by jberay            #+#    #+#              #
#    Updated: 2024/02/28 13:28:29 by jberay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo_bonus

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf

SRCS 			=	ph_check_args_bonus.c \
					ph_error_bonus.c \
					ph_init_bonus.c \
					ph_main_bonus.c \
					ph_utils_bonus.c \
					ph_forks_bonus.c \
					ph_life_bonus.c \
					ph_philo_sem_read_bonus.c \
					ph_philo_sem_write_bonus.c \
					ph_eat_routine_bonus.c \
					ft_itoa_bonus.c \
					ft_strjoin_bonus.c \
						
OBJS			=	$(SRCS:%.c=%.o)

all:				$(NAME)

$(NAME):			$(OBJS)
					$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 
					
%.o:%.c
					@$(CC) $(CFLAGS) -c $< -o $@		

clean:
					$(RM) $(OBJS)

fclean:				clean
					$(RM) $(NAME)
					
re:					fclean all

.PHONY:				all bonus clean fclean re