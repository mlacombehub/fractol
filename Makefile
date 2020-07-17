# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/25 15:14:53 by mlacombe          #+#    #+#              #
#    Updated: 2020/07/15 15:18:33 by mlacombe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# program name
NAME			=fractol

# compiler
CC				=gcc
override CFLAGS	+=-Wall -Wextra -Werror
FRAMEWORKS		=-framework OpenGL -framework AppKit
OBJ				=$(addprefix $(OBJ_DIR),$(SRC:.c=.o))
DEP				=$(addprefix $(OBJ_DIR),$(SRC:.c=.d))

# files
SRC				=main.c				\
				fol_mlx.c			\
				mandelbrot.c		\
				julia.c				\
				burningship.c

# directories
SRC_DIR			=./srcs/
INC_DIR			=./includes/
OBJ_DIR			=./objects/

# ft library
FT				=./libft/
FT_LIB			=$(addprefix $(FT),libft.a)
FT_INC			=-I ./libft/includes
FT_LNK			=-L ./libft -l ft

# mlx library
MLX				=./minilibx/
MLX_LIB			=$(addprefix $(MLX),mlx.a)
MLX_INC			=-I ./minilibx
MLX_LNK			=-L ./minilibx -lmlx $(FRAMEWORKS)

all:
	$(MAKE) $(NAME)

-include $(DEP)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INC_DIR) -MMD -o $@ -c $<

$(FT_LIB): FORCE
	$(MAKE) -C $(FT)

$(MLX_LIB):
	$(MAKE) -C $(MLX)

$(NAME): $(OBJ) $(FT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(FT) clean
	$(MAKE) -C $(MLX) clean

fclean:
	$(MAKE) -C $(FT) fclean
	$(MAKE) -C $(MLX) clean
	rm -rf $(OBJ_DIR) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

FORCE:

.PHONY : all clean fclean re FORCE
