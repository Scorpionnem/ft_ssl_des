NAME :=	ft_ssl

CC :=	cc
CFLAGS :=	-g -MP -MMD -Wall -Wextra -Werror # -fsanitize=address -fno-omit-frame-pointer
LFLAGS :=	-lm

###

INCLUDE_DIRS :=	inc/\
				inc/hash/\
				lib/libft/\
				lib/ft_printf/includes\

SRCS :=	main\
		opt\
		ctx\
		hash/md5\
		hash/sha256\
		hash/dispatch\
		print\
		input\

###

INCLUDE_DIRS :=	$(addprefix -I, $(INCLUDE_DIRS))

SRCS :=	$(addprefix src/, $(SRCS))
SRCS :=	$(addsuffix .c, $(SRCS))

###

OBJ_DIR :=	obj

OBJS =	$(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS =	$(SRCS:%.c=$(OBJ_DIR)/%.d)

###

LIBFT :=	lib/libft/libft.a
LIBFTPRINTF :=	lib/ft_printf/libftprintf.a

compile: $(LIBFTPRINTF) $(LIBFT)
	@make -j all --no-print-directory

all: $(NAME)

$(LIBFT):
	@make -C lib/libft/ all --no-print-directory

$(LIBFTPRINTF):
	@make -C lib/ft_printf/ all --no-print-directory

$(NAME): $(OBJS)
	@echo Compiling $(NAME)
	@$(CC) $(CFLAGS) $(LFLAGS) $(INCLUDE_DIRS) -o $@ $^ $(LIBFT) $(LIBFTPRINTF)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo Compiling $@
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

re: fclean compile

fclean: clean
	@echo Removed $(NAME)
	@make -C lib/libft/ fclean --no-print-directory
	@make -C lib/ft_printf/ fclean --no-print-directory
	@rm -rf $(NAME)

clean:
	@echo Removed $(OBJ_DIR)
	@make -C lib/ft_printf/ clean --no-print-directory
	@make -C lib/libft/ clean --no-print-directory
	@rm -rf $(OBJ_DIR)

.PHONY: all clean fclean re compile

-include $(DEPS)
