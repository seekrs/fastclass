NAME = class

SRCS = fastclass.c

CC = /bin/clang

PATH = /nfs/homes/${USER}/.local/bin

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}:
	@${CC} ${FLAGS} ${SRCS} -o ${PATH}/${NAME}; \
	echo "\e[1;32m[build successfull]\e[1;00m"

custom :
	@read -p "Enter your username, it will appear on your 42Header as (USERNAME@EMAIL) : " class_username; \
	read -p "Enter your email, it will appear on your 42Header as (USERNAME@EMAIL): " class_email; \
	${CC} ${FLAGS} ${SRCS} -D USER=\"$$class_username\" -D MAIL=\"$$class_email\" -o ${PATH}/${NAME}; \
	echo "\e[1;32m[build successfull]\e[1;00m"

remove: 
	/bin/rm ${PATH}/${NAME}

re:	fclean all

.PHONY : all remove re
