
NAME := philo

SRC := main.c \
	phi_parser.c \
	phi_routines01.c \
	phi_routines02.c \
	phi_lstfct_01.c \
	phi_utils01.c \
	phi_utils02.c

LIBDIR = ../libft
LIB = $(LIBDIR)/libft.a

OBJDIR = obj
OBJ = $(SRC:.c=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

CFLAGS = -Wall -Werror -Wextra  -g
LDFLAGS = -I $(LIBDIR)/ 

CC = cc

$(NAME): $(LIB) $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LIB) $(LDFLAGS) -lpthread

all: $(LIB) $(OBJ) $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $^ $(LDFLAGS)

$(LIB):
	@make -sC $(LIBDIR)

clean:
	@rm -rf $(OBJDIR)
	@make -sC $(LIBDIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re libft
