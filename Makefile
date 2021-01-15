CC			= gcc -Wall -Wextra -Werror
RM			= rm -rf
NAME		= miniRT 
NORME		= norminette
INCS_DIR	= ./includes/

MLX_DIR		= ./libraries/mlx/
MLX_INC		= -I$(MLX_DIR)
MLX_NAME	= $(MLX_DIR)libmlx.a

LIB_DIR		= ./libraries/libft/
LIB_INC		= -I$(LIB_DIR)includes/
LIB_NAME	= $(LIB_DIR)libftfull.a

LIBS		= -lXext -lX11 -lm

INCS		= $(addprefix $(INCS_DIR), minirt.h mlx_code.h)

SRCS		= $(addprefix ./sources/, minirt.c \
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

%.o			: %.c
			@$(CC) -I$(INCS_DIR) $(LIB_INC) $(MLX_INC) -c $< -o $@

all			: $(NAME)

$(NAME)		: $(OBJS) $(INCS)
			@make --silent -C $(LIB_DIR)
			@make --silent -C $(MLX_DIR)
			@$(CC) $(OBJS) $(LIB_NAME) $(MLX_NAME) -L$(LIB_DIR) -L$(MLX_DIR) \
			$(LIB_INC) $(MLX_INC) -I$(INCS_DIR) $(LIBS) -o $(NAME)
			@echo "miniRT compiled"

clean:
			@$(MAKE) clean --silent -C ./libraries/libft/
			@$(RM) $(OBJS)

fclean		: clean
			@$(MAKE) fclean --silent -C ./libraries/libft/
			@$(RM) $(NAME)

docu		:
			@$(MAKE) --silent -C ./documentation/

re			: fclean all

.PHONY		: all clean fclean re docu
