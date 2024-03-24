# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 11:38:23 by jberay            #+#    #+#              #
#    Updated: 2024/03/01 10:27:47 by jberay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -fsanitize=thread -g
RM				=	rm -rf

SRCS 			=	ph_check_args.c \
					ph_error.c \
					ph_init.c \
					ph_main.c \
					ph_utils.c \
					ph_threads.c \
					ph_life.c \
					ph_data_time_mutex.c \
					ph_data_flag_mutex.c \
					ph_philo_mutex_read.c \
					ph_philo_mutex_write.c \
					ph_thread_utils.c \
					ph_eat_routine.c \
						
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