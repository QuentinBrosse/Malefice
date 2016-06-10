##
## Makefile for Malefice in /home/trucho_g/rendu/Malefice
## 
## Made by Guillaume Truchot
## Login   <trucho_g@epitech.net>
## 
## Started on  Thu Jun  9 16:55:59 2016 Guillaume Truchot
## Last update Fri Jun 10 15:06:48 2016 Guillaume Truchot
##

CXX		=	g++

CXXFLAGS	=	-std=c++11
CXXFLAGS	+=	-m32
CXXFLAGS	+=	-I ../../Shared
CXXFLAGS	+=	-I /usr/local/include/cegui-0.8.6/
CXXFLAGS	+=	-I /usr/local/include/irrKlang-1.5.0/
CXXFLAGS	+=	-I /usr/local/include/irrlicht-1.8.3/
CXXFLAGS	+=	-I /usr/local/include/raknet/
CXXFLAGS	+=	-I /usr/local/include/spdlog/
CXXFLAGS	+=	-I /usr/local/include/tinyxml2/
CXXFLAGS	+=	-L ../../Shared
CXXFLAGS	+=	-L /usr/local/lib/cegui-0.8.6/
CXXFLAGS	+=	-L /usr/local/lib/irrKlang-1.5.0/
CXXFLAGS	+=	-L /usr/local/lib/irrlicht-1.8.3/
CXXFLAGS	+=	-L /usr/local/lib/raknet/
CXXFLAGS	+=	-L /usr/local/lib/tinyxml2/

LDFLAGS		=	-lGL -lX11 -lXxf86vm -lRakNetDLL -lLibRPC3 -lIrrlicht -lCEGUIBase-0 -lCEGUICommonDialogs-0 -lCEGUICoreWindowRendererSet -lCEGUIExpatParser -lCEGUIIrrlichtRenderer-0 -lCEGUIOpenGLRenderer-0 -lCEGUISDL2ImageCodec -lIrrKlang -lShared -ltinyxml2

RPATH           =       -Wl,-rpath='$$ORIGIN:/usr/local/lib/raknet:/usr/local/lib/tinyxml2:/usr/local/lib/irrlicht-1.8.3:/usr/local/lib/cegui-0.8.6:/usr/local/lib/irrKlang-1.5.0:../../Shared'

SRCS		=	$(wildcard *.cpp)

OBJS		=	$(SRCS:.cpp=.o)

NAME		=	client_core

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
