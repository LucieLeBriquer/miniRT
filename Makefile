CC			= gcc
#CFLAGS		= -Wall -Wextra -Werror
CFLAGS		=
RM			= rm -rf
NAME		= minirt 
LIBS		= libmlx_Linux.a libft.a -lXext -lX11 -lm
INCS		= incs/miniRT.h incs/get_next_line.h incs/mlx.h incs/libft.h
INCS_DIR	= ./incs
NORME		= ~/.norminette/norminette.rb

SRCS		= miniRT.c \
			obj/intersections.c \
			obj/obj_functions.c \
			vector/vector_norm.c \
			vector/vector_operations.c

PARS		= read/get_next_line.c \
			read/get_next_line_utils.c \
			parse/parse.c \
			parse/utils.c

OBJS		= $(SRCS:.c=.o)
PARS_OBJ	= $(PARS:.c=.o)

%.o			: %.c
			$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

all			: $(NAME)

$(NAME)		: $(OBJS) $(INCS)
			$(CC) -I$(INCS_DIR) $(OBJS) $(LIBS) -o $(NAME)
		
parse		: $(PARS_OBJ)
			$(CC) -I$(INCS_DIR) $(PARS_OBJ) $(LIBS) -o pars

norme		:
			$(NORME) $(SRCS)

clean:
			$(RM) $(OBJS) $(PARS_OBJ)

fclean		: clean
			$(RM) $(NAME) pars

re			: fclean all

.PHONY		: all clean fclean re norme parse
