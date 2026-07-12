CC = gcc

FLAGS = -fPIC -Wall -Wextra -Werror -O3 -fno-builtin -march=native

LINKFLAGS = -shared -fvisibility=hidden 

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC = bitmap.c \
	  free.c \
	  malloc.c \
	  realloc.c \
	  zone.c \
	  memcpyopt.c

OBJ =  $(SRC:.c=.o)

LINKNAME = libft_malloc.so

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LINKFLAGS) -o $(NAME) $^
	ln -sf $(NAME) $(LINKNAME)	

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) $(LINKNAME)

re: fclean all

.PHONY : all clean fclean re
