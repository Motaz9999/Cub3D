NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -g3

# Directories
SRC_DIR     = src/
INC_DIR     = Include/
LIBFT_DIR   = libft/
MLX_DIR     = minilibx-linux/
GNL_DIR     = get_next_line/

# Source files
SRCS        = $(SRC_DIR)main.c \
			  $(SRC_DIR)error/error_handling.c \
			  $(SRC_DIR)parsing/parsing.c \
			  $(SRC_DIR)parsing/extract_data.c \
			  $(SRC_DIR)parsing/check_on_path_and_value.c \
			  $(SRC_DIR)parsing/parsing_map.c \
			  $(SRC_DIR)utils/init_game.c \
			  $(SRC_DIR)utils/clean_data.c \
			  $(GNL_DIR)get_next_line.c \
			  $(GNL_DIR)get_next_line_utils.c

# Object files
OBJS        = $(SRCS:.c=.o)

# Libraries
LIBFT       = $(LIBFT_DIR)libft.a
MLX         = $(MLX_DIR)libmlx_Linux.a

# Includes and Linking
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(GNL_DIR)
LIBS        = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Colors
GREEN       = \033[0;32m
RESET       = \033[0m

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(GREEN)Building $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully compiled!$(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(GREEN)Building libft...$(RESET)"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	@echo "$(GREEN)Building minilibx...$(RESET)"
	@$(MAKE) -s -C $(MLX_DIR)

clean:
	@echo "$(GREEN)Cleaning objects...$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) clean -s -C $(LIBFT_DIR)

fclean: clean
	@echo "$(GREEN)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) fclean -s -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
