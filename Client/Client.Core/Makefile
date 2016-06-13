##
## Makefile for Malefice in /home/trucho_g/rendu/Malefice
## 
## Made by Guillaume Truchot
## Login   <trucho_g@epitech.net>
## 
## Started on  Thu Jun  9 16:55:59 2016 Guillaume Truchot
## Last update Sat Jun 11 22:39:41 2016 Guillaume Truchot
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
CXXFLAGS	+=	-I $(INCLUDE_BASE)cegui-0.8.6/
CXXFLAGS	+=	-I $(INCLUDE_BASE)irrKlang-1.5.0/
CXXFLAGS	+=	-I ../../Shared
CXXFLAGS	+=	-L $(LIB_BASE)irrlicht-1.8.3/
CXXFLAGS	+=	-L $(LIB_BASE)raknet/
CXXFLAGS	+=	-L $(LIB_BASE)tinyxml2/
CXXFLAGS	+=	-L $(LIB_BASE)cegui-0.8.6/
CXXFLAGS	+=	-L $(LIB_BASE)irrKlang-1.5.0/
CXXFLAGS	+=	-L $(LIB_BASE)dep/
CXXFLAGS	+=	-L ../../Shared

LDFLAGS		=	-lIrrlicht -lRakNetDLL -lLibRPC3 -ltinyxml2 -lCEGUIBase-0 -lCEGUICommonDialogs-0 -lCEGUICoreWindowRendererSet -lCEGUIExpatParser -lCEGUIIrrlichtRenderer-0 -lCEGUIOpenGLRenderer-0 -lCEGUISDL2ImageCodec -lIrrKlang -lShared -lfreetype -lGLEW -lGLU -lexpat -lpcre -lzlib -lpng -lSDL2 -lSDL2_image

RPATH		=	-Wl,-rpath='$$ORIGIN/lib/irrlicht-1.8.3:$$ORIGIN/../../Dependencies/LINUX/lib/irrlicht-1.8.3:$$ORIGIN/lib/raknet:$$ORIGIN/../../Dependencies/LINUX/lib/raknet:$$ORIGIN/lib/tinyxml2:$$ORIGIN/../../Dependencies/LINUX/lib/tinyxml2:$$ORIGIN/lib/cegui-0.8.6:$$ORIGIN/../../Dependencies/LINUX/lib/cegui-0.8.6:$$ORIGIN/lib/irrKlang-1.5.0:$$ORIGIN/../../Dependencies/LINUX/lib/irrKlang-1.5.0:$$ORIGIN'

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
