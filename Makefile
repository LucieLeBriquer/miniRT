CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -rf

NAME		= minirt 

LIBS		= libraries/libmlx_Linux.a \
			libraries/libft.a -lXext -lX11 -lm

INCS		= $(addprefix includes/, minirt.h \
			get_next_line.h \
			libft.h \
			mlx_code.h \
			mlx.h)

INCS_DIR	= ./includes

NORME		= ~/.norminette/norminette.rb

SRCS		= $(addprefix srcs/, minirt.c \
			display/camera.c \
			display/events.c \
			display/rendering.c \
			inter/color.c \
			inter/inter_0sphere.c \
			inter/inter_1plane.c \
			inter/inter_2square.c \
			inter/inter_3cylindre.c \
			inter/inter_4triangle.c \
			inter/inter.c \
			parse/converter.c \
			parse/get_next_line.c \
			parse/get_next_line_utils.c \
			parse/global.c \
			parse/parse.c \
			parse/skip.c \
			parse/type.c \
			parse/utils.c \
			print/print_elem.c \
			print/print_obj.c \
			print/print_parsing.c \
			vector/ray_operations.c \
			vector/vector_norm.c \
			vector/vector_operations1.c \
			vector/vector_operations2.c)

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
			$(RM) $(NAME)

re			: fclean all

.PHONY		: all clean fclean re norme
