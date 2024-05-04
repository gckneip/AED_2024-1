int finalValueAfterOperations(char** operations, int operationsSize) {
    int X = 0, i = 0, j = 0;

    for(i=0; i < operationsSize; i++){
        for(j=0; operations[i][j] != '\0'; j++){
            if(operations[i][j] == 'X'){
                continue;
            }
            if(operations[i][j] == '+'){
                X++;
            } else {
                X--; 
            }
            break;
        }
    }
    return X;
}