CC = cc
FLAGS = -Wall -Wextra -Werror

TAR_CLI = client
TAR_SER = server

SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = lib/libft
INC_DIR = includes

SRC_CLI = $(SRC_DIR)/client.c
SRC_SER = $(SRC_DIR)/server.c
OBJ_CLI = $(SRC_CLI:$(SRC_DIR)/client.c=$(OBJ_DIR)/client.o)
OBJ_SER = $(SRC_SER:$(SRC_DIR)/server.c=$(OBJ_DIR)/server.o)

LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft

HEADERS = -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(TAR_CLI) $(TAR_SER)

$(TAR_CLI): $(LIBFT) $(OBJ_CLI)
	$(CC) $(FLAGS) $(OBJ_CLI) $(HEADERS) $(LIBS) -o $(TAR_CLI)

$(TAR_SER): $(LIBFT) $(OBJ_SER)
	$(CC) $(FLAGS) $(OBJ_SER) $(HEADERS) $(LIBS) -o $(TAR_SER)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minitalk.h
	mkdir -p $(@D)
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(TAR_CLI)
	rm -rf $(TAR_SER)
	rm -rf obj

re: fclean all

.PHONY: all clean fclean re
