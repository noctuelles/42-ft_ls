SRCS_DIR=srcs
LIBFT_DIR=libft
FT_PRINTF_DIR=ft_printf
OBJS_DIR=objs
INCLUDES_DIR=includes $(LIBFT_DIR)/includes $(FT_PRINTF_DIR)/includes

SRCS=main.c \
     wrapper.c \
     sort.c \
     walk.c \
     mem.c \
     utils.c \
     parsing/opts.c

LIBFT=$(LIBFT_DIR)/libft.a
FT_PRINTF=$(FT_PRINTF_DIR)/libftprintf.a

OBJS=$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
HEADS=$(addprefix -I, $(INCLUDES_DIR))

NAME=ft_ls

CC=gcc
RM=rm -rf
MKDIR=mkdir -p

CFLAGS=-Wall -Werror -Wextra -Wpedantic -g3

DEBUG_FLAGS=

all: $(NAME)
clean:
	$(RM) $(OBJS_DIR)
fclean: clean
	$(RM) $(NAME)
re: fclean all

$(NAME): $(LIBFT) $(FT_PRINTF) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(FT_PRINTF) $(DEBUG_FLAGS) -o $@
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADS) $(DEBUG_FLAGS) -c $< -o $@
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all
$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR) all

.PHONY: all clean fclean re
