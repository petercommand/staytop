all:
	gcc -g -Wall `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0` -lX11 staytop.c send_message.c menu.c -o staytop
