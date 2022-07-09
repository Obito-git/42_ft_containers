NAME = a.out
CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g3 -fsanitize=address
SRCS_DIR = srcs/
VT = vector_test
SRCS = main.cpp benchmark.cpp stack_test.cpp all_tests.cpp subject_tests.cpp set_tests.cpp \
	vector_test.cpp map_test.cpp
OBJ/OBJECTS		=	$(patsubst $(SRCS_DIR)%.cpp, obj/%.o, $(SRCS))
SRCS	:= $(foreach file,$(SRCS),$(SRCS_DIR)$(file))

all: $(NAME)

obj/%.o: $(SRCS_DIR)%.cpp Makefile | obj
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ/OBJECTS)
	$(CC) -o $(NAME) $^ $(CFLAGS)

obj:
	mkdir obj

clean:
	rm -rf obj
	rm -f .*.swp

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
