#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isValid(char *s);
char *leString(void);


int main(void){
    char *input = leString();
    if(isValid(input) == true){
        printf("Válido!");
        free(input);
        return 0;
    } else {
        printf("Inválido");
        free(input);
        return 1;
    }
}

char *leString(void){
    int i = 0;
    char *input = (char *)calloc(1,sizeof(char)), c = '\0';
    c = getchar();

    while(c != '\n'){
        input[i++] = c;
        input = (char *)realloc(input,sizeof(char)*i);
        c = getchar();
    }
    input[i] = '\0';
    return input;
}

bool isValid(char* s) {
    int q = 0, i = 0, tam = strlen(s);
    char *foi = '\0';
    if((tam % 2) != 0){
        return false;
    }

    foi = (char *)calloc(1,sizeof(char)*(tam));

    while(s[i] != '\0'){
        switch(s[i]){
            case '(':
                foi[q] = '(';
                q++;
                break;
            case '[':
                foi[q] = '[';
                q++;
                break;
            case '{':
                foi[q] = '{';
                q++;
                break;
            case ')':
                if(q == 0 || foi[q-1] != '('){
                    return false;
                }
                q--;
                break;
            case ']':
                if(q == 0 || foi[q-1] != '['){
                    return false;
                }
                q--;
                break;
            case '}':
                if(q == 0 || foi[q-1] != '{'){
                    return false;
                }
                q--;
                break;
        }
        i++;
    }
    free(foi);
    if(q != 0){
        return false;
    }
    return true;
}