bool lemonadeChange(int* bills, int billsSize) {
    int i = 0;
    int notas10 = 0;
    int notas5 = 0;

    while(i < billsSize){
        switch(bills[i]){
            case 5:
                notas5++;
                break;
            case 10:
                if(notas5 > 0){
                    notas5--;
                    notas10++;
                    break;
                }
                return false;
            case 20:
                if(notas5 > 0 && notas10 > 0){
                    notas5--;
                    notas10--;
                    break;
                } else if(notas5 >= 3){
                    notas5 = notas5 -3;
                    break;
                 }
                return false;
        }
        i++;
    }
    return true;
}