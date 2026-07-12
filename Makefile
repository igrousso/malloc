CC = gcc
AR = ar
RM = rm -rf

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
	  memcpyopt.c \
	  show_alloc_mem.c

OBJ = $(SRC:.c=.o)

LINKNAME = libft_malloc.so
FT_PRINTF_DIR = ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ) $(FT_PRINTF_LIB)
	$(CC) $(LINKFLAGS) -o $(NAME) $(OBJ) $(FT_PRINTF_LIB)
	ln -sf $(NAME) $(LINKNAME)

$(FT_PRINTF_LIB):
	$(MAKE) -C $(FT_PRINTF_DIR) all

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME) $(LINKNAME)
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
