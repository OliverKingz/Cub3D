# **************************************************************************** #
# DIRECTORIES
SRC_DIR		:= src/
INC_DIR		:= inc/
OBJ_DIR		:= obj/
LIB_DIR		:= lib/

LIB_DIR			:= lib/
LIBMLX_DIR		:= $(LIB_DIR)MLX42/
LIBMLX_INC_DIR	:= $(LIBMLX_DIR)include/
LIBFT_DIR		:= $(LIB_DIR)libft/
LIBFT_INC_DIR	:= $(LIBFT_DIR)inc/

# **************************************************************************** #
# PROJECT
NAME		:= cub3d
LIBFT		:= $(LIBFT_DIR)libft.a
LIBMLX		:= $(LIBMLX_DIR)build/libmlx42.a

# **************************************************************************** #
# FILES
SRC_FILES	:=	main background
INC_FILES	:=	cub3d

# GENERAL FILES
SRCS	:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS	:= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS	:= $(OBJS:.o=.d)
INCS	:= $(INC_DIR)so_long.h $(LIBFT_INC_DIR)libft.h $(LIBMLX_INC_DIR)MLX42.h

# **************************************************************************** #
# COMPILER
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
CFLAGS	+= -MMD -MP
CFLAGS	+= -Wunreachable-code -Ofast
IFLAGS			:= -I$(INC_DIR) -I$(LIBFT_INC_DIR) -I$(LIBMLX_INC_DIR)
LDFLAGS			:= $(LIBFT)
LDFLAGS			+= $(LIBMLX) -ldl -lglfw -pthread -lm

# DEBUG MODE
BUILD_MODE_FILE := .build_mode
DEBUG			?= 0
VALGRIND		?= 0
VALGRIND_FLAGS	:= --leak-check=full --show-leak-kinds=all --track-origins=yes

ifeq ($(DEBUG),1)
	CFLAGS += -g3 -fsanitize=address
	LDFLAGS += -fsanitize=address
endif

ifeq ($(VALGRIND),1)
	CFLAGS += -g3
endif

# **************************************************************************** #
# COLOURS: BOLD RGBYW
BR	= \033[1;31m
BG	= \033[1;32m
BB	= \033[1;34m
BY	= \033[1;33m
BW	= \033[1;37m

# NO COLOR and CLEAR LINE
NC	= \033[0;39m
CL	= \033[2K

# **************************************************************************** #
# ESSENTIAL RULES
-include $(DEPS)

# Default rule to create the program
all: libmlx libft $(NAME)

# Rule to create the program
$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	@$(CC) $(CFLAGS) $(IFLAGS) $^ $(LDFLAGS) -o $(NAME)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(BG)Compilation success\t✅$(NC)\n"
	@echo "─────────────────────────────────────────────────────$(BY)"
	@echo "              ▗▄▄▖     ▗▖   ▗▄▄▖ ▗▄▄▄                ";
	@echo "             ▐▌        ▐▌      ▐▌▐▌  █               ";
	@echo "             ▐▌   ▐▌ ▐▌▐▛▀▚▖ ▀▀▚▖▐▌  █               ";
	@echo "             ▝▚▄▄▖▝▚▄▞▘▐▙▄▞▘▗▄▄▞▘▐▙▄▄▀               ";
	@echo "                           by ozamora- and raperez-  ";
	@echo "$(NC)─────────────────────────────────────────────────────"

# Rule to compile object files from source files
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(NC)$<\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Rule to make the library Libft
libft: $(LIBFT)
$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

# Rule to make the library Libmlx
libmlx: $(LIBMLX)
$(LIBMLX):
	-@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build > /dev/null && make -C $(LIBMLX_DIR)/build -j4 > /dev/null
	@printf "%b" "$(CL) -> $(BW)[LibMLX]:\t\t$(NC)$(BG)Compilation success\t✅$(NC)\n"

# Rule to clean generated files
clean:
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR) $(BUILD_MODE_FILE)
	@rm -rf $(LIBMLX_DIR)/build
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(BG)Object files cleaned\t❎$(NC)\n"

# Rule to clean generated files and the executable
fclean:
	@$(MAKE) clean > /dev/null
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@rm -rf $(NAME) $(BONUS_NAME)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(BG)Exe and objects cleaned\t❎$(NC)\n"

# Rule to recompile from zero
re: fclean all

# **************************************************************************** #
# NORM AND DEBUG RULES

# Rule to check if the files pass norminette
norm:
	@norminette $(SRC_DIR) $(INC_DIR)

# Rule to compile with debug flags
debug:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "DEBUG=1" $(BUILD_MODE_FILE); then \
		$(MAKE) fclean -s; \
	fi
	@echo "DEBUG=1" > $(BUILD_MODE_FILE)
	@$(MAKE) DEBUG=1 -s
	@echo " -> $(BW)[Debug]:\t\t$(BB)Debug mode enabled\t🟦$(NC)\n"
	-@./$(NAME) $(ARGS)

# Rule to compile with valgrind debug flags
valgrind:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "VALGRIND=1" $(BUILD_MODE_FILE); then \
		$(MAKE) fclean -s; \
	fi
	@echo "VALGRIND=1" > $(BUILD_MODE_FILE)
	@$(MAKE) VALGRIND=1 -s
	@echo " -> $(BW)[Valgrind]:\t\t$(BB)Valgrind mode enabled\t🟦$(NC)\n"
	-@valgrind $(VALGRIND_FLAGS) ./$(NAME) $(ARGS)

# **************************************************************************** #

.PHONY: all clean fclean re libmlx libft norm debug valgrind
.DEFAULT_GOAL := all