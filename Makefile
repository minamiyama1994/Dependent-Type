all:
	$(CXX) -Wall -Wextra -Werror -I ./include -std=c++11 -o example example.cpp
