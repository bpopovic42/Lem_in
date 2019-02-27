NAME		=	lem-in

############################## DIRS ############################################

LFTDIR		=	./libft

IDIR		=	./includes

SDIR		=	./srcs

ODIR		=	./objs

############################## SRCS ############################################

# **************************************************************************** #
# Lem_in :

PARSING_DIR	=	parsing

PARSING		=	$(addprefix  $(PARSING_DIR)/, \
		parse_input.c parse_line.c record_room_if_valid.c record_room.c \
		record_link_if_valid.c record_link.c parser_data_utils.c)

ALGO_DIR	=	algo

ALGO		=	$(addprefix $(ALGO_DIR)/, \
		get_paths.c path_utils.c set_utils.c tmp_debug_tools.c)

LMN_IO_DIR	=	io

LMN_IO		=	$(addprefix $(LMN_IO_DIR)/, \
		error_utils.c print_result.c)

LMN_FILES	=	$(addprefix $(LMNDIR)/, \
		main.c $(PARSING) $(ALGO) $(LMN_IO))

# **************************************************************************** #
# Complete path :

LMN_SRCS	=	$(addprefix $(SDIR)/, $(LMN_FILES))

############################## OBJS ############################################

LMN_OBJS	=	$(LMN_FILES:.c=.o)

LMN_OBJ		=	$(addprefix $(ODIR), $(LMN_OBJS))

OBJ			=	$(LMN_OBJ)

############################## INCS ############################################

LFT			=	$(addprefix $(LFTDIR)/, libft.a)

LFT_INC_DIR	=	$(addprefix $(LFTDIR)/, $(IDIR))

LFT_INC		=	$(addprefix $(LFTDIR)/, $(IDIR)/libft.h)

LMN_INC		=	$(addprefix $(IDIR)/, lem_in.h)

HEADERS		=	$(LFT_INC) #$(LMN_INC)

INCS		=	$(addprefix -I,$(IDIR) $(LFT_INC_DIR))

############################## COMP ############################################

CC			=	gcc

CFLAGS		=	$(DEBUG) $(if $(SILENT), , -Wall -Wextra -Werror)

############################## RULES ###########################################

all			:	$(NAME)

$(NAME)	:	$(LFT) $(LMN_OBJ) $(LMN_INC)
			@$(CC) $(CFLAGS) -o $(NAME) $(LMN_OBJ) $(LFT) $(INCS)
			@$(IF_CMP)
			@echo $(BG)[$(BLB)LEM_IN $(BG)COMPILED$(BG)]$(X)

$(ODIR)/%.o	:	$(SDIR)/%.c $(HEADERS)
			@$(CMP)
			@$(MKODIR)
			@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)
			@$(CLR)
			@echo -n $@

$(LFT)		:
		@$(IF_NO_LFT)
		@$(MAKE) DEBUG="$(DEBUG)" -C $(LFTDIR)

clean		:
	@$(MAKE) clean -C $(LFTDIR)
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf $(ODIR)
	@/bin/rm -rf $(DBGDIR)
	@echo $(BG)[$(BLB)LEM_IN $(BG)CLEANED$(BG)]$(X)

fclean		:	clean
	@/bin/rm -f $(LFT)
	@/bin/rm -f $(NAME)

re			:	fclean all

############################## UTIL ############################################

DBGDIR		=	$(NAME).dSYM

MKODIR		=	if [ ! -d $(ODIR) ]; then \
			/bin/mkdir -p $(ODIR); \
			/bin/mkdir -p $(ODIR)/$(PARSING_DIR); \
			/bin/mkdir -p $(ODIR)/$(ALGO_DIR); \
			/bin/mkdir -p $(ODIR)/$(LMN_IO_DIR); fi

CMP			=	if [ ! -e .cmp ]; then \
				echo $(BY)Compiling $(B)Project $(X)files...$(BY); \
				touch .cmp; fi

IF_CMP		=	if [ -e .cmp ]; then \
			$(CLR); \
			echo $(UP) $(CUT) $(UP); \
			/bin/rm -f .cmp; fi

IF_NO_LFT	=	if [ ! -e libft/ ]; then \
					git clone https://github.com/bpopovic42/libft; fi

############################## DISPLAY #########################################

BY			=	"\033[1;33m"
BR			=	"\033[1;31m"
BG			=	"\033[1;32m"
BLB			=	"\033[1;36m"
BP			=	"\033[1;35m"
Y			=	"\033[33m"
R			=	"\033[31m"
G			=	"\033[0;32m"
B			=	"\033[34m"
P			=	"\033[35m"
X			=	"\033[0m"
UP			=	"\033[A"
CUT			=	"\033[K"
CLR			=	printf "\r%40c\r" " "
CUT_UP		=	$(UP)$(CUT)$(UP)

############################## OTHER ###########################################

.PHONY		: all, clean, fclean, re
