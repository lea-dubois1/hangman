CC = gcc # CC pour C, CXX pour C++ = compilateur
EXEC = hangman # nom de l'éxécutable
SRC = $(wildcard *.c) # tous les fichiers qui on l'extention .c . On aurait pu faire SRC = hangman.c fileHandler.c
OBJ = $(SRC:.c=.o)

# <cible> : <dépendance(s)> = règle
all : $(EXEC)

%.o : %.c # pour créer le fichier .o, il doit y avoir un fichier .c
	$(CC) -o $@ -c $<
	# -o = nom de la sortie
	# -c = nom de la source

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^

clean :
	rm -rf $(OBJ)

mrproper : clean
	rm -rf $(EXEC)

# Variables spéciales :
# $@ = nom de la cible
# $< = nom de la première dépendance
# $^ = liste des dépendances
# $? = liste des dépendances plus récentes que la cible
# $* = nom du fichier, sans son extention