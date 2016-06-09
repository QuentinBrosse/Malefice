##
## Makefile for Malefice in /home/trucho_g/rendu/Malefice
## 
## Made by Guillaume Truchot
## Login   <trucho_g@epitech.net>
## 
## Started on  Thu Jun  9 14:14:30 2016 Guillaume Truchot
## Last update Thu Jun  9 16:28:26 2016 Guillaume Truchot
##

CXX		=	g++

CXXFLAGS	=	-std=c++11
CXXFLAGS	+=	-fPIC
CXXFLAGS	+=	-I /usr/local/include/boost-1.61.0/
CXXFLAGS	+=	-I /usr/local/include/cegui-0.8.6/
CXXFLAGS	+=	-I /usr/local/include/irrKlang-1.5.0/
CXXFLAGS	+=	-I /usr/local/include/irrlicht-1.8.3/
CXXFLAGS	+=	-I /usr/local/include/raknet/
CXXFLAGS	+=	-I /usr/local/include/spdlog/
CXXFLAGS	+=	-I /usr/local/include/tinyxml2/
CXXFLAGS	+=	-L /usr/local/lib/cegui-0.8.6/
CXXFLAGS	+=	-L /usr/local/lib/irrKlang-1.5.0/
CXXFLAGS	+=	-L /usr/local/lib/irrlicht-1.8.3/
CXXFLAGS	+=	-L /usr/local/lib/raknet/
CXXFLAGS	+=	-L /usr/local/lib/tinyxml2/

LDFLAGS		=	-ltinyxml2 -lLibRPC3 -lRakNetDLL -lIrrlicht

SRCS		=	$(wildcard *.cpp)

OBJS		=	$(notdir $(SRCS:.cpp=.o))

NAME		=	libShared.so

RM		=	rm -f


all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -shared -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re
