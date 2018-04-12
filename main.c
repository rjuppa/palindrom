#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *SEPARATORS = " .,?!-\n";

int is_separator(int c){
    if(strchr(SEPARATORS, c)){
        return 1;
    }
    return 0;
}



int load_text(char *path, char ***dictionary){
    FILE *fr;
    int idx = 0;    // index of word
    int widx = 0;   // index of char in word
    int c;          // character

    char *word;
    word = (char *)malloc(sizeof(char));

    fr = fopen(path, "r");
    while((c = getc(fr)) != EOF){
        if( is_separator(c) == 1){
            widx++;
            word = (char *)realloc(word, sizeof(char) * (widx));
            *(word + widx-1) = '\0';
            idx++;

            *dictionary = realloc(*dictionary, sizeof(char*) * (idx));
            (*dictionary)[idx-1] = word;
            widx = 0;
            word = NULL;
        }
        else{
            widx++;
            word = (char *)realloc(word, sizeof(char) * (widx));
            *(word + widx-1) = (char)tolower(c);
        }
    }
    fclose(fr);
    return idx;
}


int find_palidrom(char *word){
    int n = 0;
    int n_max = 0;
    int len = 1;
    int max = (int)strlen(word);
    int i = 1;
    while(word[i] != 0){

        if(i-len < 0){
            i++;
            continue;
        }
        if(i+len > max){
            break;
        }
        if( word[i-len] == word[i+len] ){
            len++;
            n++;
        }
        else{
            i++;
            len = 1;
            if( n > n_max ){
                n_max = n;
            }
            n = 0;
        }
    }
    return 2*n_max + 1;
}


int main(int argc, char **arg) {

    if( argc !=2 ){
        printf("Use: palindrom <filename>");
        exit(1);
    }

    int count = 0;
    char path[255] = {0};
    strcpy(path, arg[1]);

    char ***dictionary;
    dictionary = calloc((size_t)1, sizeof(char **));
    count = load_text(path, dictionary);

    char *word;
    int pl = 0;
    int pl_max = 0;
    char *winner = malloc(128 * sizeof(char));
    for(int i = 0; i < count; i++){
        word = (*dictionary)[i];
        if(word == NULL ){
            continue;
        }
        pl = find_palidrom(word);
        if( pl > pl_max ){
            pl_max = pl;
            strcpy(winner, word);
        }
        if(pl > 2){
            printf("%d - %s  %d\n", i, word, pl);
        }

        free(word);
    }

    printf("--- Palindron ------------------\n");
    printf("%s\n", winner);

    free(dictionary);
    free(winner);
    return 0;
}