##
## Makefile for Malefice in /home/trucho_g/rendu/Malefice
## 
## Made by Guillaume Truchot
## Login   <trucho_g@epitech.net>
## 
## Started on  Thu Jun  9 14:14:30 2016 Guillaume Truchot
## Last update Fri Jun 10 16:59:23 2016 Guillaume Truchot
##

INCLUDE_BASE	=	../Dependencies/LINUX/include/
LIB_BASE	=	../Dependencies/LINUX/lib/

CXX		=	g++

CXXFLAGS	=	-std=c++11
CXXFLAGS	+=	-m32
CXXFLAGS	+=	-fPIC
CXXFLAGS	+=	-I $(INCLUDE_BASE)irrlicht-1.8.3/
CXXFLAGS	+=	-I $(INCLUDE_BASE)raknet/
CXXFLAGS	+=	-I $(INCLUDE_BASE)spdlog/
CXXFLAGS	+=	-I $(INCLUDE_BASE)tinyxml2/
CXXFLAGS	+=	-L $(LIB_BASE)irrlicht-1.8.3/
CXXFLAGS	+=	-L $(LIB_BASE)raknet/
CXXFLAGS	+=	-L $(LIB_BASE)tinyxml2/

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
