# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 17:25:10 by igrousso          #+#    #+#              #
#    Updated: 2024/11/18 07:09:53 by igrousso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
AR = ar
RM = rm -rf

EXEC = exec

CFLAGS += -Wall -Wextra -Werror -fPIC

NAME = libftprintf.a

SRC = ft_printf.c \
	  ft_printc.c \
	  ft_prints.c \
	  ft_printd.c \
	  ft_printu.c \
	  ft_printx.c \
	  ft_printX.c \
	  ft_printp.c \
	  ft_ul_itoa_base.c \
	  ft_ui_itoa_base.c \
	  tools.c \
	  tools2.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) 
	$(AR) rcs $@ $(OBJ)  

$(EXEC) : $(OBJ) 
	$(CC) -o $(EXEC) $(OBJ) 

%.o : %.c 
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME) $(EXEC)

re : fclean all

.PHONY : all clean fclean re