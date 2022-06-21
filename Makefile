NAME = a.out
CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g3 
SRCS_DIR = srcs/
VT = vector_test
SRCS = inception_main.cpp \
	$(VT)/random_access_operator_test.cpp $(VT)/constructor_destructor_test.cpp \
	$(VT)/capacity_and_access.cpp $(VT)/modifiers.cpp
OBJ/OBJECTS		=	$(patsubst $(SRCS_DIR)%.cpp, obj/%.o, $(SRCS))
SRCS	:= $(foreach file,$(SRCS),$(SRCS_DIR)$(file))

all: $(NAME)

obj/%.o: $(SRCS_DIR)%.cpp Makefile | obj
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ/OBJECTS)
	$(CC) -o $(NAME) $^ $(CFLAGS)

obj:
	mkdir obj
	mkdir obj/vector_test

clean:
	rm -rf obj
	rm -f .*.swp

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
