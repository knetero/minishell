# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/28 23:37:39 by gghaya            #+#    #+#              #
#    Updated: 2023/08/19 12:45:49 by abazerou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
FLAGS =  -Wall -Werror -Wextra
CFILES = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
				ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
				ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_strtrim.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_striteri.c ft_strmapi.c
OFILES = ${CFILES:.c=.o}
HEADER = libft.h
all : ${NAME}

${NAME} : ${OFILES} ${HEADER}
	@ar -crs ${NAME} ${OFILES}

%.o:%.c ${HEADER}
	@${CC} -c ${FLAGS} $<

clean :
	@rm -f ${OFILES}

fclean : clean
	@rm -f ${NAME}

re : fclean all 

.PHONY: clean fclean re all
