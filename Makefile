NAME := philo

SRC := main.c \
	phi_parser.c \
	phi_routines01.c \
	phi_routines02.c \
	utils/phi_lstfct_01.c \
	utils/phi_utils01.c \
	utils/phi_utils02.c \
	utils/phi_utils03.c

OBJDIR = obj
OBJ = $(SRC:.c=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

CFLAGS = -Wall -Werror -Wextra -g 

CC = cc

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LIB) -lpthread

all: $(OBJ) $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
