##################################################################### BEG_1 ####

NAME		:= cub3D

# ---------------------------------------------------------------------------- #
#   VARIABLES                                                                  #
# ---------------------------------------------------------------------------- #
LIBS		:= ft mlx m X11 Xext
LIBS_TARGET	:=	\
	lib/libft/libft.a	\
	lib/minilibx-linux/libmlx.a

INCS		:= $(INCS) inc $(dir $(LIBS_TARGET))
INCS		:= $(INCS) inc $(addsuffix inc,$(dir $(LIBS_TARGET)))

SRC_DIR		:= src
SRCS		:=	\
	main.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRCS_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP -I inc
LDFLAGS		:= $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS		:= $(addprefix -l,$(LIBS))

# ---------------------------------------------------------------------------- #
#   SHELL COMMANDS                                                             #
# ---------------------------------------------------------------------------- #
RM		:= rm -f
MAKE		:= $(NAME) --jobs --silent --no-print-directory
DIR_DUP		= mkdir -p $(@D)
VALGRIND	:= valgrind -q --leak-check=full --show-leak-kinds=all --trackfds=yes
ERR_MUTE	:= 2>/dev/null

# ---------------------------------------------------------------------------- #
#   BUILD & EXTRA RULES                                                        #
# ---------------------------------------------------------------------------- #
all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $(NAME))

LIBS_TARGET:
	$(MAKE) -C $(@D) $(ERR_MUTE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

run-%: $(NAME)
	-./$(NAME) $*

vrun-%: $(CFLAGS) += -g3
vrun-%: $(NAME)
	-$(VALGRIND) ./$(NAME) $*

malloc_test: $(OBJS)
	cc -Wall -Wextra -Werror -g -fsanitize=undefined -rdynamic -o $@ $(OBJS) -Ltest/ft_mallocator -lmallocator

info-%:
	$(MAKE) --dry-run --always-make $* | grep -V "info"

print-%:
	$(info '$*'='$($*)')

update:
	git stash
	git pull
	git submodule update --init
	git stash pop

norminette:
	norminette inc
	norminette src

asan: CFLAGS	+= -O0 -g3 -fsanitize=address,undefined,integer -fno-optimize-sibling-calls
asan: LDFLAGS	+= -g3 -fsanitize=address,undefined,integer
asan: all

every: CFLAGS	+= -Weverything
every: all

# ---------------------------------------------------------------------------- #
#   SPECIAL TARGETS                                                            #
# ---------------------------------------------------------------------------- #
.PHONY: clean fclean re norminette
.SILENT:

##################################################################### END_1 ####
