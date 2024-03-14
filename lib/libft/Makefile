##################################################################### BEG_1 ####

NAME		:= libft.a

# ---------------------------------------------------------------------------- #
#   VARIABLES                                                                  #
# ---------------------------------------------------------------------------- #
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

CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -MMD -MP -I include
AR		:= ar
ARFLAGS		:= -r -c -s

# ---------------------------------------------------------------------------- #
#   SHELL COMMANDS                                                             #
# ---------------------------------------------------------------------------- #
RM		:= rm -f
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(@D)

# ---------------------------------------------------------------------------- #
#   BUILD & EXTRA RULES                                                        #
# ---------------------------------------------------------------------------- #
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	$(info CREATED $(NAME))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

norminette:
	norminette inc
	norminette src

# ---------------------------------------------------------------------------- #
#   SPECIAL TARGETS                                                            #
# ---------------------------------------------------------------------------- #
.PHONY: clean fclean re norminette
.SILENT:

##################################################################### END_1 ####
