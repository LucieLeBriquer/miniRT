CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

NAME		= minirt 

LIBS		= libraries/libmlx_Linux.a \
			libraries/libftfull.a -lXext -lX11 -lm

INCS		= $(addprefix includes/, minirt.h \
			get_next_line.h \
			libft.h \
			mlx_code.h \
			mlx.h)

INCS_NR		= $(addprefix includes/, minirt.h \
			get_next_line.h \
			libft.h)

INCS_DIR	= ./includes

SRCS		= $(addprefix sources/, minirt.c \
			display/camera.c \
			display/errors.c \
			display/events.c \
			display/rendering.c \
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
			raytracing/color.c \
			raytracing/inter_0sphere.c \
			raytracing/inter_1plane.c \
			raytracing/inter_2square.c \
			raytracing/inter_3cylindre.c \
			raytracing/inter_4triangle.c \
			raytracing/inter.c \
			vector/color_operations.c \
			vector/ray_operations.c \
			vector/vector_geometry.c \
			vector/vector_norm.c \
			vector/vector_operations.c)

OBJS		= $(SRCS:.c=.o)

%.o			: %.c
			@$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

all			: $(NAME)

$(NAME)		: $(OBJS) $(INCS) libs
			@echo -n "Compiling all objs for miniRT\t\t"
			@$(CC) -I$(INCS_DIR) $(OBJS) $(LIBS) -o $(NAME)
			@echo "OK"

libs		:
			@echo -n "Updating libft...\t\t\t"
			@$(MAKE) --no-print-directory -s -C ./libraries/libft/
			@cp ./libraries/libft/libftfull.a ./libraries
			@echo "OK"

norme		:
			@norminette $(SRCS)
			@$(MAKE) --no-print-directory norme -C ./libraries/libft/

clean:
			@echo -n "Cleaning objs from miniRT\t\t"
			@$(RM) $(OBJS)
			@echo "OK"

fclean		: clean
			@echo -n "Deleting ./minirt\t\t\t"
			@$(RM) $(NAME)
			@echo "OK"

libclean	:
			@echo -n "Cleaning libft...\t\t\t"
			@$(MAKE) --no-print-directory fclean -C ./libraries/libft/
			@rm ./libraries/libftfull.a
			@echo "OK"

re			: fclean libclean all

.PHONY		: all clean fclean re libs norme libclean
