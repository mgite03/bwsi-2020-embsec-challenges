

int main(){
    char[] str1= "nope/0"
    
    str_compare()
}

int str_compare(char* str1, char* str2){
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0'){
        if (str1[i] > str2[i])
            return 1;
        if (str1[i] < str2[i])
            return -1;
        i++;
    }
    return 0;
}