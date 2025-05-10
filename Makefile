#				______ _ _
#				|  ____(_) |
#				| |__   _| | ___  ___
#				|  __| | | |/ _ \/ __|
#				| |    | | |  __/\__ \.
#				|_|    |_|_|\___||___/

HEADERS			=	lem-ipc.h

SRCS			=	main.c

LIBFTSRC		=	libftprintf.a libft.a printffd.a

MLXSRC			=	libmlx.a

#					Directories

MLXDIR			=	./mlx_lin/

UTILSDIR		=	./srcs/utils/

HEADERSDIR		=	./inc/

SRCSDIR			=	./srcs/

LIBFTDIR		=	./libft/

OBJSDIR			=	./.objs/

#					Full Path

MLX			=	$(addprefix $(MLXDIR),$(MLXSRC))

HEAD		=	$(addprefix $(HEADERSDIR),$(HEADERS))

SRCSPATH	=	$(addprefix $(SRCSDIR),$(SRCS))

LIBFT		=	$(addprefix $(LIBFTDIR),$(LIBFTSRC))

OBJS		=	$(addprefix $(OBJSDIR), $(SRCSPATH:.c=.o))

#		 __      __        _       _     _
#		 \ \    / /       (_)     | |   | |
#		  \ \  / /_ _ _ __ _  __ _| |__ | | ___  ___
#		   \ \/ / _` | '__| |/ _` | '_ \| |/ _ \/ __|
#		    \  / (_| | |  | | (_| | |_) | |  __/\__ \.
#		     \/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/

define HEADER
"\e[2J\e[H
\033[1;36m
 ___      _______  __   __         ___   _______  _______
|   |    |       ||  |_|  |       |   | |       ||   ____|
|   |    |    ___||       | ____  |   | |    _  ||  |
|   |    |   |___ |       ||____| |   | |   |_| ||  |
|   |___ |    ___||       |       |   | |    ___||  |
|       ||   |___ | ||_|| |       |   | |   |    |  |____
|_______||_______||_|   |_|       |___| |___|    |_______|
\033[0m
endef
export HEADER

RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
CYAN		=	\033[1;36m
DEFAULT		=	\033[0m
SUPPR		=	\r\033[2K

NAME		=	lem-IPC

AR			=	ar rc

FLAGS		=	-lX11 -lXext -L$(MLXDIR)

CFLAGS		=	-Wall -Wextra -Werror

CC			=	cc

RM			=	rm -rf

MKDIR		=	mkdir -p

MUTE		:=	1

#				  _____       _
#				 |  __ \     | |
#				 | |__) |   _| | ___  ___
#				 |  _  / | | | |/ _ \/ __|
#				 | | \ \ |_| | |  __/\__ \.
#				 |_|  \_\__,_|_|\___||___/

all : header lib ${NAME}

${NAME}: $(OBJS) $(LIBFT)
ifeq ($(MUTE),1)
	@${CC} ${OBJS} ${LIBFT} -o ${NAME} $(FLAGS) -lm
	@echo -n "${SUPPR} ${GREEN}	${NAME} : 🆗${DEFAULT}\n"
else
	${CC} ${OBJS} ${LIBFT} -o ${NAME} $(FLAGS)
endif

$(OBJSDIR)%.o: %.c ${HEAD}
	@$(MKDIR) .objs
	@$(MKDIR) $(dir $@)
ifeq ($(MUTE),1)
	@echo -n "${YELLOW}${SUPPR}	⌛ Creating ft_ping objects : $@"
	@$(CC) ${CFLAGS} -c $< -o $@ -I$(HEADERSDIR) -Ilibft/includes
else
	$(CC) ${CFLAGS} -c $< -o $@ -I$(HEADERSDIR) -Ilibft/includes
endif

clean:
	@${MAKE} clean -C ${LIBFTDIR}
	@${RM} ${OBJS}

fclean:
	@echo "${RED}🗑  ${NAME} cleanded"
	@${RM} ${OBJS}
	@${RM} ${OBJSDIR}
	@${RM} ${NAME}
	@${MAKE} fclean --no-print-directory -C ${LIBFTDIR}
	@${MAKE} clean --no-print-directory  --silent -C ${MLXDIR}

reobj:
	rm -rf $(OBJSDIR)
	@${MAKE} --no-print-directory all

header:
	@echo "$$HEADER"

re:
	@${MAKE} --no-print-directory fclean
	@${MAKE} --no-print-directory all

lib:
	@${MAKE} --no-print-directory  --silent -C ${MLXDIR}
	@echo "\033[1A${SUPPR}${GREEN}	LIBMLX : 🆗${DEFAULT}"
	@${MAKE} --no-print-directory -C ${LIBFTDIR}

.PHONY : re all clean fclean printf lib header
