##
## Makefile for Malefice in /home/trucho_g/rendu/Malefice
## 
## Made by Guillaume Truchot
## Login   <trucho_g@epitech.net>
## 
## Started on  Thu Jun  9 20:45:51 2016 Guillaume Truchot
## Last update Fri Jun 10 17:14:51 2016 Guillaume Truchot
##

INCLUDE_BASE	=	../../Dependencies/LINUX/include/
LIB_BASE	=	../../Dependencies/LINUX/lib/

CXX		=	g++

CXXFLAGS	=	-std=c++11
CXXFLAGS	+=	-m32
CXXFLAGS	+=	-I $(INCLUDE_BASE)irrlicht-1.8.3/
CXXFLAGS	+=	-I $(INCLUDE_BASE)raknet/
CXXFLAGS	+=	-I $(INCLUDE_BASE)spdlog/
CXXFLAGS	+=	-I $(INCLUDE_BASE)tinyxml2/
CXXFLAGS	+=	-I ../../Shared
CXXFLAGS	+=	-L $(LIB_BASE)irrlicht-1.8.3/
CXXFLAGS	+=	-L $(LIB_BASE)raknet/
CXXFLAGS	+=	-L $(LIB_BASE)tinyxml2/
CXXFLAGS	+=	-L ../../Shared

LDFLAGS		=	-lIrrlicht -lRakNetDLL -lLibRPC3 -ltinyxml2 -lShared

RPATH		=	-Wl,-rpath='$$ORIGIN/lib/irrlicht-1.8.3:$$ORIGIN/lib/raknet:$$ORIGIN/lib/tinyxml2:$$ORIGIN'

SRCS		=	$(wildcard *.cpp)

OBJS		=	$(SRCS:.cpp=.o)

NAME		=	server_core

RM		=	rm -f


all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(RPATH) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re
