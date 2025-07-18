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
NAME		:= cub3D
LIBFT		:= $(LIBFT_DIR)libft.a
LIBMLX		:= $(LIBMLX_DIR)build/libmlx42.a

# **************************************************************************** #
# FILES
SRC_FILES	:= debug draw_minimap draw_raycast draw_utils draw exit_utils exit \
			hook init_game init_scene main map_check map move parser raycast_dda \
			raycast_utils raycast rgb utils utils2 utils3
INC_FILES	:=	cub3d

# GENERAL FILES

SRCS	:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS	:= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS	:= $(OBJS:.o=.d)
INCS	:= $(INC_DIR)cub3D.h $(LIBFT_INC_DIR)libft.h $(LIBMLX_INC_DIR)MLX42.h

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
VALGRIND_FLAGS	:= --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=doc/valgrind.supp --log-file=doc/memcheck.log --gen-suppressions=all

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
all: libft libmlx $(NAME)

# Rule to create the program
$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	@$(CC) $(CFLAGS) $(IFLAGS) $^ $(LDFLAGS) -o $(NAME)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(NC)$(BG)Compilation success\t✅$(NC)\n"
	@$(MAKE) -s print_banner

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
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build > /dev/null && make -C $(LIBMLX_DIR)/build -j4 > /dev/null
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

print_banner:
		@echo "─────────────────────────────────────────────────────$(BY)"
		@echo "              ▗▄▄▖     ▗▖   ▗▄▄▖ ▗▄▄▄                ";
		@echo "             ▐▌        ▐▌      ▐▌▐▌  █               ";
		@echo "             ▐▌   ▐▌ ▐▌▐▛▀▚▖ ▀▀▚▖▐▌  █               ";
		@echo "             ▝▚▄▄▖▝▚▄▞▘▐▙▄▞▘▗▄▄▞▘▐▙▄▄▀               ";
		@echo "                           by ozamora- and raperez-  ";
		@echo "$(NC)─────────────────────────────────────────────────────"

# **************************************************************************** #
# BONUS SECTION 

# BONUS DIRECTORIES
SRC_BONUS_DIR	:= src/bonus/
INC_BONUS_DIR	:= inc/bonus/
OBJ_BONUS_DIR	:= obj/bonus/

# BONUS FILES
BONUS_NAME	:= cub3D_bonus
# SRCS_BONUS_FILES	:= $(addprefix $(SRC_BONUS_DIR), $(addsuffix .c, $(SRC_BONUS_FILES)))
SRC_BONUS_FILES	:= $(wildcard $(SRC_BONUS_DIR)*.c)
INC_BONUS_FILES	:= cub3d_bonus

# BONUS GENERAL FILES
# OBJS_BONUS	:= $(SRCS_BONUS:$(SRC_BONUS_DIR)%.c=$(OBJ_BONUS_DIR)%.o)
OBJS_BONUS	:= $(addprefix $(OBJ_BONUS_DIR), $(notdir $(SRC_BONUS_FILES:.c=.o)))
DEPS_BONUS	:= $(OBJS_BONUS:.o=.d)
INCS_BONUS	:= $(INC_BONUS_DIR)cub3d_bonus.h $(LIBFT_INC_DIR)libft.h $(LIBMLX_INC_DIR)MLX42.h

# BONUS COMPILER FLAGS
IFLAGS_BONUS:= -I$(INC_BONUS_DIR) -I$(LIBFT_INC_DIR) -I$(LIBMLX_INC_DIR)

# BONUS RULES
bonus: libft libmlx $(BONUS_NAME)
$(BONUS_NAME): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(IFLAGS_BONUS) $(OBJS_BONUS) $(LDFLAGS) -o $(BONUS_NAME)
	@printf "%b" "$(CL) -> $(BW)[$(BONUS_NAME)]:\t$(BG)Bonus compiled\t\t✅$(NC)\n"
	@$(MAKE) -s print_banner

$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)
$(OBJ_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c | $(OBJ_BONUS_DIR)
	@mkdir -p $(dir $@)
	@printf "%b" "$(CL) -> $(BW)[$(BONUS_NAME)]:\t$(NC)$<\r"
	@$(CC) $(CFLAGS) $(IFLAGS_BONUS) -c $< -o $@

# **************************************************************************** #
# NORM AND DEBUG RULES

DEFAULT_MAP := example
MAP ?= $(DEFAULT_MAP)

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
	-@./$(NAME) assets/scenes/$(MAP).cub

# Rule to compile with valgrind debug flags
valgrind:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "VALGRIND=1" $(BUILD_MODE_FILE); then \
		$(MAKE) fclean -s; \
	fi
	@echo "VALGRIND=1" > $(BUILD_MODE_FILE)
	@$(MAKE) VALGRIND=1 -s
	@echo " -> $(BW)[Valgrind]:\t\t$(BB)Valgrind mode enabled\t🟦$(NC)\n"
	-@valgrind $(VALGRIND_FLAGS) ./$(NAME) assets/scenes/$(MAP).cub

# Rule to run the program with a specific map
# Example usage: make run MAP=subject
run: all
	-@./$(NAME) assets/scenes/$(MAP).cub

# Rule to compile bonus with debug flags
bdebug:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "DEBUG=1" $(BUILD_MODE_FILE); then \
		$(MAKE) fclean -s; \
	fi
	@echo "DEBUG=1" > $(BUILD_MODE_FILE)
	@$(MAKE) bonus DEBUG=1 -s
	@echo " -> $(BW)[Debug]:\t\t$(BB)Debug mode enabled\t🟦$(NC)\n"
	-@./$(BONUS_NAME) assets/scenes/$(MAP)_bonus.cub

# Rule to compile with valgrind debug flags
bvalgrind:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "VALGRIND=1" $(BUILD_MODE_FILE); then \
		$(MAKE) fclean -s; \
	fi
	@echo "VALGRIND=1" > $(BUILD_MODE_FILE)
	@$(MAKE) bonus VALGRIND=1 -s
	@echo " -> $(BW)[Valgrind]:\t\t$(BB)Valgrind mode enabled\t🟦$(NC)\n"
	-@valgrind $(VALGRIND_FLAGS) ./$(BONUS_NAME) assets/scenes/$(MAP)_bonus.cub

# Rule to run the bonus program with a specific map
# Example usage: make brun MAP=wolfenstein_bonus
brun: bonus
	-@./$(BONUS_NAME) assets/scenes/$(MAP)_bonus.cub

# **************************************************************************** #
# ADDITIONAL RULES

# Rule to show help
help:
	@echo "$(BY)Available targets:$(NC)"
	@echo "  $(BB)all$(NC)       - Build the project"
	@echo "  $(BB)clean$(NC)     - Remove object files"
	@echo "  $(BB)fclean$(NC)    - Remove object files and executable"
	@echo "  $(BB)re$(NC)        - Rebuild the project from scratch"
	@echo "  $(BB)bonus$(NC)     - Build the bonus part of the project"
	@echo "  $(BB)norm$(NC)      - Check code with norminette"
	@echo "  $(BB)debug$(NC)     - Build the project with debug flags"
	@echo "  $(BB)valgrind$(NC)  - Build the project with valgrind flags"
	@echo "  $(BB)help$(NC)      - Show this help message"
	@echo "  $(BB)show$(NC)      - Show compilation and linking commands"
	@echo "  $(BB)info$(NC)      - Show all variables being used"

# Rule to show compilation and linking commands
show:
	@echo "$(BY)Compilation command:$(NC)\t"\
		"$(CC) $(CFLAGS) $(IFLAGS) -c $(SRC_DIR)$(NAME).c -o $(OBJ_DIR)$(NAME).o"
	@echo "$(BY)Linking command:$(NC)\t"\
		"$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)"
	@echo "$(BY)Cleaning command:$(NC)\t rm -rf $(NAME) $(BONUS_NAME)"\
		"$(OBJ_DIR)*.o $(OBJ_DIR)*.d $(OBJ_DIR) $(BUILD_MODE_FILE)"
	@echo "$(BY)Valgrind command:$(NC)\t"\
		"valgrind $(VALGRIND_FLAGS) ./$(NAME) $(ARGS)"

# Rule to show all variables being used
info:
	@echo "$(BY)\nozamora's Project:$(NC)"
	@echo "$(BB)NAME: $(NC)$(NAME)"
	@echo "$(BB)LIBFT: $(NC)$(LIBFT)"
	@echo "$(BB)BONUS_NAME: $(NC)$(BONUS_NAME)"
	@echo "$(BY)\nCompiler:$(NC)"
	@echo "$(BB)CC: $(NC)$(CC)"
	@echo "$(BB)CFLAGS: $(NC)$(CFLAGS)"
	@echo "$(BB)IFLAGS: $(NC)$(IFLAGS)"
	@echo "$(BB)LDFLAGS: $(NC)$(LDFLAGS)"
	@echo "$(BY)\nDirectories:$(NC)"
	@echo "$(BB)SRC_DIR: $(NC)$(SRC_DIR)"
	@echo "$(BB)INC_DIR: $(NC)$(INC_DIR)"
	@echo "$(BB)OBJ_DIR: $(NC)$(OBJ_DIR)"
	@echo "$(BB)LIB_DIR: $(NC)$(LIB_DIR)"
	@echo "$(BB)LIBFT_DIR: $(NC)$(LIBFT_DIR)"
	@echo "$(BB)LIBFT_INC_DIR: $(NC)$(LIBFT_INC_DIR)"
	@echo "$(BY)\nFiles:$(NC)"
	@echo "$(BB)NAME: $(NC)$(NAME)"
	@echo "$(BB)SRC_FILES: $(NC)$(SRC_FILES)"
	@echo "$(BB)INC_FILES: $(NC)$(INC_FILES)"
	@echo "$(BB)SRCS: $(NC)$(SRCS)"
	@echo "$(BB)OBJS: $(NC)$(OBJS)"
	@echo "$(BB)DEPS: $(NC)$(DEPS)"
	@echo "$(BB)INCS: $(NC)$(INCS)"
	@echo "$(BY)\nBonus:$(NC)"
	@echo "$(BB)BONUS_NAME: $(NC)$(BONUS_NAME)"
	@echo "$(BB)SRC_BONUS_FILES: $(NC)$(SRC_BONUS_FILES)"
	@echo "$(BB)INC_BONUS_FILES: $(NC)$(INC_BONUS_FILES)"
	@echo "$(BB)SRCS_BONUS: $(NC)$(SRCS_BONUS)"
	@echo "$(BB)OBJS_BONUS: $(NC)$(OBJS_BONUS)"
	@echo "$(BB)DEPS_BONUS: $(NC)$(DEPS_BONUS)"
	@echo "$(BB)INCS_BONUS: $(NC)$(INCS_BONUS)"
	@echo "$(BB)IFLAGS_BONUS: $(NC)$(IFLAGS_BONUS)"

.PHONY: all clean fclean re libmlx libft norm debug valgrind bonus bdebug bvalgrind brun
.DEFAULT_GOAL := all