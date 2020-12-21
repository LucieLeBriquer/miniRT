CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
NAME		= minirt 
LIBS		= libraries/libmlx_Linux.a \
			libraries/libft.a -lXext -lX11 -lm
INCS		= incs/miniRT.h incs/get_next_line.h incs/mlx.h incs/libft.h
INCS_DIR	= ./incs
NORME		= ~/.norminette/norminette.rb

SRCS		= $(addprefix srcs/, minirt.c \
			color/color.c \
			inter/inter.c \
			inter/inter_0sphere.c \
			inter/inter_1plane.c \
			inter/inter_2square.c \
			inter/inter_3cylindre.c \
			inter/inter_4triangle.c \
			vector/vector_norm.c \
			vector/vector_operations1.c \
			vector/vector_operations2.c \
			vector/ray_operations.c \
			read/get_next_line.c \
			read/get_next_line_utils.c \
			parse/converter.c \
			parse/global.c \
			parse/parse.c \
			parse/skip.c \
			parse/type.c \
			parse/utils.c \
			print/print_elem.c \
			print/print_obj.c \
			print/print_parsing.c)

OBJS		= $(SRCS:.c=.o)

%.o			: %.c
			$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

all			: $(NAME)

$(NAME)		: $(OBJS) $(INCS)
			$(CC) -I$(INCS_DIR) $(OBJS) $(LIBS) -o $(NAME)
		
norme		:
			$(NORME) $(SRCS)

clean:
			$(RM) $(OBJS)

fclean		: clean
			$(RM) $(NAME) pars

re			: fclean all

.PHONY		: all clean fclean re norme
