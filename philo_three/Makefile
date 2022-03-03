# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mpeerdem <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/01 11:14:11 by mpeerdem      #+#    #+#                  #
#    Updated: 2020/11/09 13:20:23 by mpeerdem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		philo_three
HEADER =	philo_three.h
CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
SDIR =		srcs
ODIR =		objs
_OBJS =		main philosopher philosopher_actions \
			init utils time processes death_checker destroy
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
