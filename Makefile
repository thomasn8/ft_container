# SRCS		=		tests/main_ftvector.cpp
# SRCS		=		tests/main_stdvector.cpp
SRCS		=		tests/main_map.cpp
# SRCS		=		tests/main_stack.cpp
# SRCS		=		tests/main_intranet.cpp
# SRCS		=		tests/main_complexe.cpp

SRCS_BONUS	=		bonus/main_set.cpp

OBJS		= ${SRCS:.cpp=.o}
OBJS_BONUS	= ${SRCS_BONUS:.cpp=.o}
CC			= c++
CFLAGS		= -std=c++98 -Wall -Wextra -Werror
NAME		= containers
NAME_BONUS	= ./bonus/containers_bonus
RM			= rm -f

all:		${NAME}

${NAME}:	${OBJS}
			$(CC) $(CFLAGS) -o $(NAME) ${OBJS}

bonus:		${OBJS_BONUS}
			$(CC) $(CFLAGS) -o $(NAME_BONUS) ${OBJS_BONUS}

clean:
			${RM} ${OBJS}
			${RM} ${OBJS_BONUS}
			${RM} ./tests/main_*.o

fclean:		clean
			${RM} ${NAME}
			${RM} ${NAME_BONUS}

re:			fclean all

run:		
			./${NAME}

runbonus:		
			./${NAME_BONUS}

.PHONY:		all clean fclean re run bonus runbonus