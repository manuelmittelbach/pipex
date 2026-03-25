NAME = pipex

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
INC = pipex_bonus.h pipex.h

BONUS_DIR = bonus/

SRC = \
ft_split.c \
libft_utils.c \
pipex.c \
error_handling.c \
helpers.c \
execute_command.c

SRC_BONUS = \
ft_split.c \
libft_utils.c \
helpers.c \
error_handling.c \
$(BONUS_DIR)pipex_bonus.c \
$(BONUS_DIR)get_next_line_bonus.c \
$(BONUS_DIR)here_doc_bonus.c \
$(BONUS_DIR)multiple_pipes_bonus.c \
$(BONUS_DIR)error_handling_bonus.c \
$(BONUS_DIR)cleanup_bonus.c \
$(BONUS_DIR)execute_command_bonus.c 

OBJ = ${SRC:.c=.o}
OBJ_BONUS = ${SRC_BONUS:.c=.o}

DEP = $(OBJ:.o=.d) $(OBJ_BONUS:.o=.d)

all: ${NAME}

${NAME}: ${OBJ}
	$(CC) ${CFLAGS} $(INCLUDE) ${OBJ} -o ${NAME}

bonus: fclean ${OBJ_BONUS}
	$(CC) $(CFLAGS) $(INCLUDE) ${OBJ_BONUS} -o ${NAME}

%.o: %.c $(INC)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f ${OBJ} ${OBJ_BONUS} ${DEP}

fclean: clean
	rm -f ${NAME}

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re bonus