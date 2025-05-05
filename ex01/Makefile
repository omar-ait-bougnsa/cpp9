name = RPN
CC = c++
flag = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp 

OBJ = $(SRC:.cpp=.o)

all : $(name)

$(name) : $(OBJ)
	$(CC) $(flag) $(OBJ) -o $(name)
%.o : %.cpp
	$(CC) $(flgas) $(flag) -c $< -o $@

clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(name)
re: fclean all

.PHONY : all fclean clean re