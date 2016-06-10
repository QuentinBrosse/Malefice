##
## Makefile for Malefice in /home/trucho_g/rendu/Malefice
## 
## Made by Guillaume Truchot
## Login   <trucho_g@epitech.net>
## 
## Started on  Thu Jun  9 14:14:30 2016 Guillaume Truchot
## Last update Fri Jun 10 14:34:54 2016 Guillaume Truchot
##

CXX		=	g++

CXXFLAGS	=	-std=c++11
CXXFLAGS	+=	-m32
CXXFLAGS	+=	-fPIC
CXXFLAGS	+=	-I /usr/local/include/irrlicht-1.8.3/
CXXFLAGS	+=	-I /usr/local/include/raknet/
CXXFLAGS	+=	-I /usr/local/include/spdlog/
CXXFLAGS	+=	-I /usr/local/include/tinyxml2/
CXXFLAGS	+=	-L /usr/local/lib/irrlicht-1.8.3/
CXXFLAGS	+=	-L /usr/local/lib/raknet/
CXXFLAGS	+=	-L /usr/local/lib/tinyxml2/

#LDFLAGS		=	-ltinyxml2 -lLibRPC3 -lRakNetLibStatic -lIrrlicht
LDFLAGS		=	

SRCS		=	$(wildcard *.cpp)

OBJS		=	$(SRCS:.cpp=.o)

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
