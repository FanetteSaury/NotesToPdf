CC = gcc
CFLAGS = -Wall -Wextra -g `pkg-config --cflags gtk+-3.0 gdk-pixbuf-2.0 cairo`
LDFLAGS = `pkg-config --libs gtk+-3.0 gdk-pixbuf-2.0 cairo` -lm
SRC = src/main.c src/NotesToPdf.c
OBJ = main.o NotesToPdf.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

main.o: src/main.c src/NotesToPdf.h
	$(CC) $(CFLAGS) -c $< -o $@

NotesToPdf.o: src/NotesToPdf.c src/NotesToPdf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
