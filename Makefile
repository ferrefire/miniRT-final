CC = gcc
CFLAGS = -Iincludes/ -Iexternal/libft -Iexternal/minilibx -Wall -Wall -Werror
LDFLAGS = -Lexternal/libft -Lexternal/minilibx -lft -lm -lmlx -lX11 -lXi -lXext

SRCDIR = sources
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJDIR = objects
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
DEPS = includes/*.h
MLX = external/minilibx/libmlx.a
LIBFT = external/libft/libft.a
NAME = miniRT

.PHONY: run clean fclean re

$(NAME): $(LIBFT) $(MLX) $(OBJDIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LDFLAGS)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C external/libft

$(MLX):
	$(MAKE) all -C external/minilibx

run: $(NAME)
	./$(NAME)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) clean -C external/libft

fclean: clean
	$(MAKE) clean -C external/minilibx
	$(MAKE) fclean -C external/libft
	rm -f $(NAME)

re: fclean $(NAME)