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
			vector/vector_norm.c \
			vector/vector_operations.c \
			vector/ray_operations.c \
			read/get_next_line.c \
			read/get_next_line_utils.c \
			parse/converter.c \
			parse/global.c \
			parse/parse.c \
			parse/skip.c \
			parse/type.c \
			parse/utils.c

OBJS		= $(SRCS:.c=.o)

%.o			: %.c
			$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

all			: $(NAME)

$(NAME)		: $(OBJS) $(INCS)
			$(CC) -I$(INCS_DIR) $(OBJS) $(LIBS) -o $(NAME)
		
norme		:
			$(NORME) $(SRCS)

clean:
			$(RM) $(OBJS) $(PARS_OBJ)

fclean		: clean
			$(RM) $(NAME) pars

re			: fclean all

.PHONY		: all clean fclean re norme parse
