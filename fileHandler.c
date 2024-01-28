#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "fileHandler.h"

/// \brief Check if the file exist and if the user have the rights to open it and initialize the stream variable
/// \param dicoPath path to the file to check
/// \param stream stream for the file
/// \return "ok" if there is no errors, the message to display if there is
char* checkFileErrors(char *dicoPath, FILE **stream){
    char *message = "";

    if(access(dicoPath, F_OK) == 0){
        if(access(dicoPath, R_OK) == 0){
            if((*stream = fopen(dicoPath, "r")) != NULL){
                message = "ok";
            }
            else{
                message = "An inexpected error occured while opening the file %s\nError num : %i\n", dicoPath, errno;
            }
        }
        else{
            message = "You do not have the permission to read the file %s\n", dicoPath;
        }
    }
    else{
        message = "The file %s does not exist.\n", dicoPath;
    }

    return message;
}

/// \brief Check if there is any error in the input line
/// \param line the line to check
/// \param separator separator to split the line
/// \return 0 if there is no error\n
///         1 if the line is a comment\n
///         2 if one or more of the elements is NULL\n
///         3 if the difficulty is not facile/moyen/difficile
int handleOneLineFile(char *line, char *separator){

    if(line[0] == '#'){ // ignore comments
        return 1;
    }

    // get the word, the category and the difficulty of the line
    char *word = strtok(line, separator);
    char *wordCategory = strtok(NULL, separator);
    char *wordDifficulty = strtok(NULL, separator);

    if(word == NULL || wordCategory == NULL || wordDifficulty == NULL){
        return 2;
    }

    if(strcmp(wordDifficulty, "facile") != 0 || strcmp(wordDifficulty, "moyen") != 0 || strcmp(wordDifficulty, "difficile") != 0){
        return 3;
    }

    // Check with the arguments

    return 0;
}

/// \brief Return an array of the lines that can be used for the game (is not a comment, no element is NULL, difficulty is facile/moyen/difficile)
/// \param separator
/// \return
char** getLines(int maxWords, int maxLettersOneLine, FILE **stream, char *separator){
    char **lines = malloc(sizeof(char*) * maxWords + 1);
    char *oneLine;
    int numLineInArray = 0, numLine = 0;

    char line[maxLettersOneLine];
    while(fgets(line, maxLettersOneLine, *stream) != NULL){ // for each line of the file
        oneLine = malloc(sizeof(char) * maxLettersOneLine);

        switch (handleOneLineFile(line, separator)) {
            case 0: // Line is ok, add it to array
                strcpy(oneLine, line);
                lines[numLineInArray] = oneLine;
                numLineInArray++;
                break;

            case 1: // ignore the line (comments, lines not used) no error message
                break;

            case 2: // one or more of the elements is NULL
                printf("Incorrect number of elements on line %i : %s", numLine, line);
                break;

            case 3: // difficulty is not facile/moyen/difficile
                printf("Incorrect difficulty on line %i : %s", numLine, line);
                break;

            default:
                printf("Unexpected error on line %i : %s", numLine, line);
                break;
        }
        numLine++;
    }
    lines[numLineInArray] = "\0";
    return lines;
}