typedef struct Stack {
    char *palavra;
    char *topo;
    int limite;
} Stack;

bool Push(Stack *pilha,char letra);
void Pop(Stack *pilha);

int maximumGain(char* s, int x, int y) {
    int i = 0;
    Stack *pilha = NULL;
    int soma =0;

    if((pilha = (Stack *)malloc(sizeof(Stack))) == NULL){
        exit(EXIT_FAILURE);
    }

    pilha->limite = 0;
    pilha->topo = NULL;

    while(s[i] != '\0'){
        if(pilha->topo == 'b' && s[i] == 'a') {
            printf("Tirou %c %c\n",pilha->topo, s[i]);
            Pop(pilha);
            soma += y;
        } else if (pilha->topo == 'a' && s[i] == 'b') {
            printf("Tirou %c %c\n",pilha->topo, s[i]);
            Pop(pilha);
            soma += x;
        } else{
            Push(pilha,s[i]);
            i++;
        }
    }

    return soma;
}

bool Push(Stack *pilha,char letra){
    int i = 0;
    char *palavra;
    pilha->limite++;

    if ((palavra = (char *)malloc(sizeof(char)*pilha->limite)) == NULL){
        exit(EXIT_FAILURE);
    }

    while(i < pilha->limite-1){
        palavra[i] = pilha->palavra[i];
        i++;
    }

    pilha->palavra = palavra;

    pilha->palavra[pilha->limite -1] = letra;
    pilha->topo = pilha->palavra[pilha->limite-1];

    return true;
}

void Pop(Stack *pilha){
    int i = 0;
    char *palavra;

    if(pilha->topo == NULL){
        return;
    }

    pilha->limite--;

    if ((palavra = (char *)malloc(sizeof(char)*pilha->limite)) == NULL){
        exit(EXIT_FAILURE);
    }

    while(i < pilha->limite-1){
        palavra[i] = pilha->palavra[i];
        i++;
    }

    pilha->palavra = palavra;

    pilha->topo = pilha->palavra[pilha->limite-1];

    return;
}
