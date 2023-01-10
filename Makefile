NAME		=	webserv

SRCS		=	main.cpp \
				server.cpp \
				parsing_utils.cpp \
				location.cpp \
				web.cpp \
				parsing_request.cpp \
				env.cpp \
				ft_split.cpp \
				execFile.cpp \
				execGET_POST.cpp \

OBJS		=	$(SRCS:.cpp=.o)
CC			=	c++
FLAGS		=	-Wall -Wextra -Werror -g3 -std=c++98 -fsanitize=address
INC_PATH	=	-I./incs
COMPILE		=	$(CC) $(FLAGS) $(INC_PATH)

%.o : %.cpp
			$(CC) $(FLAGS) $(INC_PATH) -c $<  -o $(<:.cpp=.o)

all:		$(NAME)

$(NAME):	${OBJS}
			$(COMPILE) $(OBJS) -o $(NAME)

clean:
			rm -f ${OBJS}

fclean:
			rm -f ${OBJS}
			rm -f ${NAME}

re:			fclean all

.PHONY:		clean fclean all re
