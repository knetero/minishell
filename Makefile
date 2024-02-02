# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 22:15:05 by abazerou          #+#    #+#              #
#    Updated: 2023/08/20 22:44:27 by abazerou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = parsing/main.c  parsing/add_back.c  parsing/delete.c  parsing/env.c  parsing/signals.c  parsing/redirection.c  parsing/help1.c parsing/countword.c \
		parsing/heredoc.c  parsing/lstfinal.c  parsing/parsing_tree.c  parsing/parsing_two.c  parsing/parsing.c  parsing/help.c  parsing/redirection_two.c \
		parsing/newlenght.c parsing/show_final.c execution/execve/exec.c execution/builtins/echo/echo.c execution/builtins/echo/echo_option.c execution/builtins/pwd.c \
		execution/builtins/cd/cd.c execution/builtins/cd/cd_utils.c execution/builtins/exit.c execution/builtins/env.c \
		execution/builtins/unset.c execution/execve/execve.c execution/execve/child_utils.c execution/tools/other_utils.c\
		execution/export/export.c execution/export/export_utils.c execution/export/export_parsing.c  parsing/helpfunction.c\
		execution/export/export_helpers.c execution/execve/execve_utils.c execution/execve/exec_utils.c execution/tools/other_tools_helpers.c\
		execution/redirections/redirections.c execution/execve/exec_utils_helper.c execution/tools/other_tools.c

LIBFT_FILES = ft_libft/ft_memset.c ft_libft/ft_bzero.c ft_libft/ft_memcpy.c ft_libft/ft_memmove.c ft_libft/ft_memchr.c ft_libft/ft_memcmp.c ft_libft/ft_strlen.c ft_libft/ft_isalpha.c ft_libft/ft_isdigit.c ft_libft/ft_isalnum.c \
				ft_libft/ft_isascii.c ft_libft/ft_isprint.c ft_libft/ft_toupper.c ft_libft/ft_tolower.c ft_libft/ft_strchr.c ft_libft/ft_strrchr.c ft_libft/ft_strncmp.c ft_libft/ft_strlcpy.c ft_libft/ft_strlcat.c ft_libft/ft_strnstr.c \
				ft_libft/ft_atoi.c ft_libft/ft_calloc.c ft_libft/ft_strdup.c ft_libft/ft_substr.c ft_libft/ft_strjoin.c ft_libft/ft_split.c ft_libft/ft_itoa.c ft_libft/ft_putchar_fd.c ft_libft/ft_strtrim.c \
				ft_libft/ft_putendl_fd.c ft_libft/ft_putnbr_fd.c ft_libft/ft_putstr_fd.c ft_libft/ft_striteri.c ft_libft/ft_strmapi.c
NAME = minishell

BUILDDIR = build

OFILES = $(addprefix $(BUILDDIR)/,$(CFILES:.c=.o))

CC = cc 
FLAGS =  -Wall -Werror -Wextra
LIBFTDIR = ft_libft
LIBFT = ft_libft/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(BUILDDIR) $(OFILES) minishell.h $(CFILES)
	@$(CC) $(FLAGS) $(LIBFT) $(OFILES) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -o $(NAME)
	@echo "\033[0;32m✔ Minishell Made"

$(LIBFT):$(LIBFT_FILES)
	@echo "\033[0;32m✔ Building libft..."
	@$(MAKE) -C $(LIBFTDIR)

$(BUILDDIR)/%.o: %.c minishell.h
	@mkdir -p $(dir $@)
	@$(CC) -c $(FLAGS) $< -I /Users/$(USER)/.brew/opt/readline/include -o $@

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

clean:
	@rm -f $(OFILES)
	@$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: clean fclean re all
