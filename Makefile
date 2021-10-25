# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/22 23:19:50 by bmangin           #+#    #+#              #
#    Updated: 2021/10/24 09:57:30 by bmangin          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# ******************************************************* #
# *********************   VARIABLES   ******************* #
# ******************************************************* #

NAME		:= philo

PATH_I		:= includes
PATH_S		:= srcs
PATH_B		:= .bin

VPATH	= ${PATH_I} ${PATH_S} ${PATH_B}

FILES		= main.c init.c tools.c philo_action.c error.c test.c

SRCS		= ${addprefix ${PATH_S}/, ${FILES}}
OBJS		= ${FILES:.c=.o}
BIN			= ${addprefix ${PATH_B}/, ${OBJS}}

H_FILES		:= philo.h
HEADER		= ${addprefix ${PATH_I}/, ${H_FILES}}


# ******************************************************* #
# *******************   COMMANDES   ********************* #
# ******************************************************* #

CC			:= clang
FLAGS		:= -Wall -Wextra -Werror -glldb
FS			:= -g3 -fsanitize=address
CCF			:= ${CC} ${FLAGS}
CCFS		:= ${CC} ${FLAGS} ${FS}
INC			:= -I${PATH_I}
LIB			:= -lpthread
MAKE		:= make -C
CP			:= cp 
MKDIR		:= mkdir -p
RM			:= rm -rf
NORM		:= norminette

# ******************************************************* #
# *******************   MAKE SHIT   ********************* #
# ******************************************************* #

all:	crea_b ${NAME}

${PATH_B}/%.o:	%.c ${HEADER}
		${CCF} ${INC} -c $< -o $@

${NAME}:	${BIN} ${HEADERS}
		${CCF} ${INC} ${BIN} -o $@ ${LIB}

fs:		crea_b ${BIN} ${HEADER}
		${CCFS} ${INC} ${BIN} -o ${NAME} ${LIB}

crea_b :
	mkdir -p ${PATH_B}
	${shell mkdir -p ${PATH_B}}

clean:
	$(RM) $(PATH_B)

fclean: clean
	$(RM) $(NAME) $(NAME).dSYM

re: fclean all

seg: fclean fs

norm:
	${NORM} ${SRCS} ${HEADER}
	$(MAKE) ./$(PATH_L) norm
	
.PHONY:		all crea_b fs seg bonus clean fclean re seg norm
