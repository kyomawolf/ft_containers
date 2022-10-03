### VARS

NAME	= containers-ISO668

SRC_DIR	= ./
SRC		= main.cpp

HDR	=  vector.hpp iterator.hpp pair.hpp compare.hpp integral.hpp stack.hpp tree.hpp map.hpp

OBJ_DIR	= obj/
OBJ		= $(addprefix $(OBJDIR), $(SRC:.cpp=.o))

FLAGS	= -Wall -Wextra -g -std=c++98 -fsanitize=address#-Werror

all : $(OBJ_DIR) $(NAME) $(HDR)

$(NAME) : $(OBJ) $(HDR)
	c++ $(FLAGS) $(OBJ) -g -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp $(HDR)
	c++ $(FLAGS) -c $< -o $@

re : fclean all

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)