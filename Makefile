CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
NAME		= miniRT 
NORME		= norminette
INCS_DIR	= ./includes

LIBS		= libraries/libmlx_Linux.a \
			libraries/libftfull.a -lXext -lX11 -lm

INCS		= $(addprefix includes/, minirt.h \
			libftfull.h \
			mlx_code.h \
			mlx.h)

SRCS		= $(addprefix sources/, minirt.c \
			display/bitmap.c \
			display/camera.c \
			display/errors.c \
			display/events.c \
			display/init.c \
			display/legend.c \
			display/progress.c \
			display/rendering.c \
			parse/converter.c \
			parse/count.c \
			parse/global.c \
			parse/parse.c \
			parse/skip.c \
			parse/objs/circle.c \
			parse/objs/closed_cylinder.c \
			parse/objs/cone.c \
			parse/objs/cube.c \
			parse/objs/cylinder.c \
			parse/objs/plane.c \
			parse/objs/pyramide.c \
			parse/objs/sphere.c \
			parse/objs/square.c \
			parse/objs/triangle.c \
			parse/options.c \
			raytracing/color.c \
			raytracing/inter_0sphere.c \
			raytracing/inter_1plane.c \
			raytracing/inter_2square.c \
			raytracing/inter_3cylinder.c \
			raytracing/inter_4triangle.c \
			raytracing/inter_5cone.c \
			raytracing/inter_6circle.c \
			raytracing/inter.c \
			raytracing/filters.c \
			vector/color_operations.c \
			vector/ray_operations.c \
			vector/vector_geometry.c \
			vector/vector_norm.c \
			vector/vector_operations.c)

OBJS		= $(SRCS:.c=.o)

SHELL		= bash

%.o			: %.c
			@echo -ne "\rCompiling all objs for miniRT\t\t"
			@$(CC) $(CFLAGS) $(MAC_KEYS) -I$(INCS_DIR) -c $< -o $@

all			: $(NAME)

$(NAME)		: $(LIBS) $(OBJS) $(INCS)
			@$(CC) $(CFLAGS) -I$(INCS_DIR) $(MAC_KEYS) $(OBJS) $(LIBS) -o $(NAME)
			@echo "OK"

$(LIBS)		:
			@echo -ne "Updating libft\t\t\t\t"
			@$(MAKE) --no-print-directory -s -C ./libraries/libft/
			@cp ./libraries/libft/libftfull.a ./libraries
			@cp ./libraries/libft/includes/libftfull.h ./includes
			@echo "OK"

norme		:
			@norminette $(SRCS) $(INCS)
			@$(MAKE) --no-print-directory norme -C ./libraries/libft/

clean:
			@echo -ne "Cleaning objs from miniRT\t\t"
			@$(RM) $(OBJS)
			@echo "OK"

fclean		: clean
			@$(RM) $(NAME)

libclean	:
			@echo -ne "Cleaning libft\t\t\t\t"
			@$(MAKE) --no-print-directory fclean -C ./libraries/libft/
			@$(RM) ./libraries/libftfull.a
			@echo "OK"

docu		:
			@$(MAKE) --no-print-directory -s -C ./documentation/

re			: fclean libclean all

.PHONY		: all clean fclean re norme libclean docu
