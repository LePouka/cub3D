################################################################# BEG_LIBFT ####

NAME		:= libft.a

# ---------------------------------------------------------------------------- #
#   INGREDIENTS                                                                #
# ---------------------------------------------------------------------------- #
# SRC_DIR   source directory
# SRCS      source files
#
# BUILD_DIR object directory
# OBJS      object files
# DEPS      dependency files
#
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags

SRC_DIR		:= src
SRCS		:=	\
	mandatory/ft_atoi.c	\
	mandatory/ft_itoa.c	\
	mandatory/ft_bzero.c	\
	mandatory/ft_split.c	\
	mandatory/ft_strdup.c	\
	mandatory/ft_calloc.c	\
	mandatory/ft_memcmp.c	\
	mandatory/ft_memchr.c	\
	mandatory/ft_memcpy.c	\
	mandatory/ft_memset.c	\
	mandatory/ft_strchr.c	\
	mandatory/ft_substr.c	\
	mandatory/ft_strlen.c	\
	mandatory/ft_strcmp.c	\
	mandatory/ft_strjoin.c	\
	mandatory/ft_memmove.c	\
	mandatory/ft_strlcpy.c	\
	mandatory/ft_isalpha.c	\
	mandatory/ft_strmapi.c	\
	mandatory/ft_strnstr.c	\
	mandatory/ft_strtrim.c	\
	mandatory/ft_tolower.c	\
	mandatory/ft_strlcat.c	\
	mandatory/ft_isalnum.c	\
	mandatory/ft_isascii.c	\
	mandatory/ft_isdigit.c	\
	mandatory/ft_isprint.c	\
	mandatory/ft_strncmp.c	\
	mandatory/ft_strrchr.c	\
	mandatory/ft_toupper.c	\
	mandatory/ft_striteri.c	\
	mandatory/ft_putnbr_fd.c	\
	mandatory/ft_putstr_fd.c	\
	mandatory/ft_putendl_fd.c	\
	mandatory/ft_putchar_fd.c	\
	mandatory/ft_intlen.c	\
	bonus/ft_lstmap.c	\
	bonus/ft_lstnew.c	\
	bonus/ft_lstlast.c	\
	bonus/ft_lstsize.c	\
	bonus/ft_lstiter.c	\
	bonus/ft_lstclear.c	\
	bonus/ft_lstdelone.c	\
	bonus/ft_lstadd_back.c	\
	bonus/ft_lstadd_front.c	\
	ft_dprintf/ft_putu_fd.c	\
	ft_dprintf/ft_dprintf.c	\
	ft_dprintf/ft_putnbr_base_fd.c	\
	get_next_line/get_next_line.c	\
	get_next_line/get_next_line_utils.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

CFLAGS		:= -Wall -Wextra -Werror -g3
CPPFLAGS	:= -MMD -MP -Iinclude
AR		:= ar
ARFLAGS		:= -r -c -s

# ---------------------------------------------------------------------------- #
#   UTENSILS                                                                   #
# ---------------------------------------------------------------------------- #
# RM        force remove
# MAKE      quietly make
# DIR_DUP   duplicate directory tree
#
# CRUSH     used to print on the same line
# ECHO      echo statement
# R         red color output
# G         green color output
# END       reset color output to default

RM		:= rm -r -f
MAKE		:= $(MAKE)  --jobs --no-print-directory
DIR_DUP		= mkdir -p $(@D)

CRUSH		:= \r\033[K
ECHO		:= echo -n "$(CRUSH)"
R		:= $(shell tput setaf 1)
G		:= $(shell tput setaf 2)
END		:= $(shell tput sgr0)

# ---------------------------------------------------------------------------- #
#   RECIPES                                                                    #
# ---------------------------------------------------------------------------- #
# all       default goal
# $(NAME)   link .o -> library
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# update	update the repo to its most recent version

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	$(ECHO)"$(G)CREATED$(END) $(@)\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(ECHO)"$(G)CREATED$(END) $(@)"

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

update:
	git stash
	git pull
	git submodule update --init
	git stash pop

# ---------------------------------------------------------------------------- #
#   DIFFERENT CGLAGS BUILD                                                     #
# ---------------------------------------------------------------------------- #
# asan		address sanitizer
# ansi		ansi c89 compliance
# every		all warnings

asan: CFLAGS	+= -O0 -g3 -fsanitize=address,undefined,integer -fno-optimize-sibling-calls
asan: all

ansi: CFLAGS	+= -W -pedantic -std=c89
ansi: all

every: CFLAGS	+= -Weverything
every: all

# ---------------------------------------------------------------------------- #
#   TESTS                                                                      #
# ---------------------------------------------------------------------------- #

norm:
	norminette | grep -v "OK" || true

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v "info"

print-%:
	$(info '$*'='$($*)')

# ---------------------------------------------------------------------------- #
#   SPECIAL TARGETS                                                            #
# ---------------------------------------------------------------------------- #
.PHONY: clean fclean re update asan ansi every norm
.SILENT:

################################################################# END_LIBFT ####
