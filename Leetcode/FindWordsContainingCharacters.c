/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findWordsContaining(char** words, int wordsSize, char x, int* returnSize) {
    int* array = NULL, i = 0, j = 0, c =0;
    *returnSize = 0;

    while( i < wordsSize ){
        j = 0;
        while( words[i][j] != '\0' ){
            if ( words[i][j] == x ){
                c++;
                printf("%d",(sizeof(int)*(c))/4);
                if((array = (int*)realloc(array,(sizeof(int)*(c))))== NULL){
                    exit(EXIT_FAILURE);
                };
                array[c-1] = i;
                break;
            }
            j++;
        }
        i++;
    }
    *returnSize = c;
    return array;

}