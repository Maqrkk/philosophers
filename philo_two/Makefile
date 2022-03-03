# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mpeerdem <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/19 13:27:08 by mpeerdem      #+#    #+#                  #
#    Updated: 2020/11/02 10:57:51 by mpeerdem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		philo_two
HEADER =	philo_two.h
CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
SDIR =		srcs
ODIR =		objs
_OBJS =		main philosopher philosopher_actions \
			init destroy utils time death_checker
OBJS =		$(addsuffix .o, $(addprefix $(ODIR)/, $(_OBJS)))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -lpthread

$(ODIR)/%.o: $(SDIR)/%.c $(HEADER)
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
