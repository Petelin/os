void clean_concole(){
    int i,j;
    for(i=0;i<25;i++){
        for(j=0;j<80;j++){
            _putline(" ",i,j);
        }
    }
}

void _putline(char *s,int row, int cow){
    char * Buffer = (char *)0xb8000;
    while( *s != '\0'){
        *(Buffer++ + row * 160 + cow*2) = *s++;
        *(Buffer++ + row * 160 + cow*2) = 0x0f;
    }
}
