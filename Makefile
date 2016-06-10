##
## Makefile for Malefice in /home/trucho_g/rendu/Malefice
## 
## Made by Guillaume Truchot
## Login   <trucho_g@epitech.net>
## 
## Started on  Fri Jun 10 16:35:04 2016 Guillaume Truchot
## Last update Fri Jun 10 16:44:33 2016 Guillaume Truchot
##

SHARED_NAME		=	libShared.so
CLIENT_CORE_NAME	=	client_core
SERVER_CORE_NAME	=	server_core

SHARED_DIR		=	Shared/
CLIENT_CORE_DIR		=	Client/Client.Core/
SERVER_CORE_DIR		=	Server/Server.Core/
OUTPUT_DIR		=	Binaries/Debug/

SHARED_PATH		=	$(SHARED_DIR)$(SHARED_NAME)
CLIENT_CORE_PATH	=	$(CLIENT_CORE_DIR)$(CLIENT_CORE_NAME)
SERVER_CORE_PATH	=	$(SERVER_CORE_DIR)$(SERVER_CORE_NAME)

CP			=	cp

RM			=	rm -f



all: $(SHARED_PATH) $(CLIENT_CORE_PATH) $(SERVER_CORE_PATH)

$(SHARED_PATH):
	$(MAKE) -C $(SHARED_DIR) all
	$(CP) $(SHARED_PATH) $(OUTPUT_DIR)

$(CLIENT_CORE_PATH):
	$(MAKE) -C $(CLIENT_CORE_DIR) all
	$(CP) $(CLIENT_CORE_PATH) $(OUTPUT_DIR)

$(SERVER_CORE_PATH):
	$(MAKE) -C $(SERVER_CORE_DIR) all
	$(CP) $(SERVER_CORE_PATH) $(OUTPUT_DIR)

clean:
	$(MAKE) -C $(SHARED_DIR) clean
	$(MAKE) -C $(CLIENT_CORE_DIR) clean
	$(MAKE) -C $(SERVER_CORE_DIR) clean

fclean:
	$(MAKE) -C $(SHARED_DIR) fclean
	$(MAKE) -C $(CLIENT_CORE_DIR) fclean
	$(MAKE) -C $(SERVER_CORE_DIR) fclean
	$(RM) $(OUTPUT_DIR)$(SHARED_NAME)
	$(RM) $(OUTPUT_DIR)$(CLIENT_CORE_NAME)
	$(RM) $(OUTPUT_DIR)$(SERVER_CORE_NAME)


re: fclean all


.PHONY: all clean fclean re

