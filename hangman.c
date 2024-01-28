#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "fileHandler.h"

/// \brief Delete the spaces at the beginning and the end of the string.
/// \param src the string to trim
/// \return the trimmed string
char *myTrim(char *src){
    int i = 0;
    int debut = 0;
    int firstTime = 1;

    while(src[i] != 0){
        if(src[i] != ' ' && src[i] != '\t' && src[i] != '\n' && src[i] != '\r' && src[i] != '\v' && src[i] != '\f'){
            if(firstTime == 1){
                debut = i;
                firstTime = 0;
            }
        }
        i++;
    }

    int fin = 0;
    int firstTimeEnd = 1;

    while(i >= 0){
        if(src[i] != ' ' && src[i] != '\t' && src[i] != '\n' && src[i] != '\r' && src[i] != '\v' && src[i] != '\f' && src[i] != 0){
            if(firstTimeEnd == 1){
                fin = i;
                firstTimeEnd = 0;
            }
        }
        i--;
    }

    int newStrLen = fin - debut + 2;

    char *result = (char*)malloc(sizeof(char) * newStrLen);

    int j = debut;

    while(j <= fin){
        result[j - debut] = src[j];
        j++;
    }

    return result;
}

/// \brief Set the dicoPath, level and category variables with the data from args inputs
/// \param numParam the number of given params in the args array
/// \param args array of user's input
/// \param dicoPath path to the dictionary
/// \param level difficulty of the game
/// \param category category of words
void setVariables(int numParam, char **args, char **dicoPath, char **level, char **category){
    switch (numParam) {
        case 4:
            *category = args[3];
        case 3:
            if(strcmp(args[2], "facile") == 0 || strcmp(args[2], "moyen") == 0 || strcmp(args[2], "difficile") == 0 || strcmp(myTrim(args[2]), "") == 0){
                *level = args[2];
            }
            else{
                printf("Invalid difficulty. Try with : facile, moyen or difficile.\n");
            }
        case 2:
            if(strstr(args[1], ".txt") != NULL){
                *dicoPath = args[1];
            }
            else{
                printf("Invalid dictionary path. The path must end with '.txt'.\nThe dictionary is now set to default.\n");
                *dicoPath = "dictionnaire.txt";
            }
            break;
        case 1:
            *dicoPath = "dictionnaire.txt";
            break;
        default:
            printf("Invalid number of arguments.\nThe command can be used like : ./hangman [path to dictionary] [facile/moyen/difficile] <category>\n");
    }
}

int main(int numParam, char **args){
    char *separator;
    char *defaultDicoPath;
    int maxLetterOneLine = 30, maxWords = 50;

    char *dicoPath = "", *level = "", *category = "", *message;
    FILE *stream;

    setVariables(numParam, args, &dicoPath, &level, &category);
    message = checkFileErrors(dicoPath, &stream);

    if(strcmp(message, "ok") == 0){ // if the file exist and if it can be read

        char **lines = getLines(maxWords, maxLetterOneLine, &stream, separator);

        // si lines est vide, message d'erreur
        if(strcmp(lines[0], "\0") == 0){
            printf("There is no usable words in the file %s, the default dictionary will be used.", dicoPath);
            dicoPath = defaultDicoPath;
            // jsp quoi faire, trouver un truc
        }
    }
    else{
        printf("%s", message);
    }
}