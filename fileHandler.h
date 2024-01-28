#ifndef HANGMAN_FILEHANDLER_H
#define HANGMAN_FILEHANDLER_H

char* checkFileErrors(char *dicoPath, FILE **stream);
char** getLines(int maxWords, int maxLettersOneLine, FILE **stream, char *separator);

#endif //HANGMAN_FILEHANDLER_H
