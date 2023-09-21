#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
        // setup variables
        FILE *stream;
        char ch;
        int wc;
        int in_word;
        int lock;

        // check number of arguements
        if (argc != 2){
                printf("Invalid Use.\nmywc [filename]\n");
                return 0;
        }

        // setup stream + check  the file exists / can be opened
        if ((stream = fopen(argv[1], "r")) == NULL){
                printf("File cannot be opened.\n");
        }

        // until EOF is reached, get the next character
        while ((ch = fgetc(stream)) != EOF) {
                // if character is a seperation character
                if (ch != ' ' && ch != '\n'){
                        // check that we wasnt just inside a word
                        if (lock == 0){
                                // count the first seperation character
                                // and lock until we encounter the next word
                                wc += 1;
                                lock = 1;
                        }
                } else {
                        // remove the lock while inside a word
                        lock = 0;
                }
        }

        // print the number of words in the file
        printf("Number of words: %d\n", wc);
        fclose(stream);
        return 0;
}