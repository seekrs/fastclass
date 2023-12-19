NAME = class

SRCS = fastclass.c \
		42_header.c

CC = clang

INSTALL_PATH ?= $(HOME)/.local/bin

FLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}:
	@${CC} ${FLAGS} ${SRCS} -o ${NAME}; \
	printf "\e[1;32m[build successfull]\e[1;00m\n"

install : 
	@read -p "Enter your username, it will appear on your 42Header as (USERNAME@EMAIL) : " class_username; \
	read -p "Enter your email, it will appear on your 42Header as (USERNAME@EMAIL): " class_email; \
	${CC} ${FLAGS} ${SRCS} -D USER=\"$$class_username\" -D MAIL=\"$$class_email\" -o $(INSTALL_PATH)/${NAME}; \
	printf "\e[1;32m[build successfull]\e[1;00m\n"

remove:
	rm $(INSTALL_PATH)/${NAME}

re:	remove install

.PHONY : all remove install re
