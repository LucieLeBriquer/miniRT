CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -rf

NAME		= minirt 

LIBS_LIN	= libraries/libmlx_Linux.a \
			libraries/libftfull.a -lXext -lX11 -lm

LIBS_MAC	= -framework OpenGL -framework AppKit -lm \
			libraries/libmlx_mac.a libraries/libftfull.a

NORME		= ~/.norminette/norminette.rb

UNAME		:= $(shell uname -s)

ifeq ($(UNAME), Darwin)
	LIBS		= $(LIBS_MAC)
else
	LIBS		= $(LIBS_LIN)
endif

ifeq ($(UNAME), Darwin)
	MAC_KEYS	= -D MAC
endif

INCS		= $(addprefix includes/, minirt.h \
			libftfull.h \
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
			display/init.c \
			display/progress.c \
			display/rendering.c \
			parse/converter.c \
			parse/global.c \
			parse/parse.c \
			parse/skip.c \
			parse/obj1.c \
			parse/obj2.c \
			parse/options.c \
			print/bmp.c \
			print/print_elem.c \
			print/print_obj.c \
			print/print_parsing.c \
			raytracing/color.c \
			raytracing/inter_0sphere.c \
			raytracing/inter_1plane.c \
			raytracing/inter_2square.c \
			raytracing/inter_3cylinder.c \
			raytracing/inter_4triangle.c \
			raytracing/inter_5cone.c \
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
			@$(CC) $(CFLAGS) $(MAC_KEYS) -I$(INCS_DIR) -c $< -o $@

all			: $(NAME)

$(NAME)		: $(OBJS) $(INCS) libs
			@echo -ne "Compiling all objs for miniRT\t\t"
			@$(CC) -I$(INCS_DIR) $(MAC_KEYS) $(OBJS) $(LIBS) -o $(NAME)
			@echo "OK"

libs		:
			@echo -ne "Updating libft\t\t\t\t"
			@$(MAKE) --no-print-directory -s -C ./libraries/libft/
			@cp ./libraries/libft/libftfull.a ./libraries
			@cp ./libraries/libft/includes/libftfull.h ./includes
			@echo "OK"

norme		:
			@$(NORME) $(SRCS) $(INCS)
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

.PHONY		: all clean fclean re libs norme libclean docu
