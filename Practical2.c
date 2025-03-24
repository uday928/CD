#include<stdio.h>
#include<ctype.h>
// to use isalpha,tolower,isdigit etc functions
#include<string.h>
// strlen function
#define MAX 100
int main(){
    int digitCount=0;
    int vowelCount=0;
    int symbolCount=0;
    char str[MAX];
    printf("Enter the sentence:");
    // fgets(str,sizeof(str),stdin);
    gets(str);
    int length=strlen(str);
    for(int i=0;i<length;i++){
        str[i]=tolower(str[i]);
        if(isdigit(str[i])){
            digitCount+=1;
        }
        else if(isalpha(str[i])){
            if(str[i]=='a' || str[i]=='e' || str[i]=='i' || str[i]=='o' || str[i]=='u'){
                vowelCount+=1;
            }
        }
        else if(!(isspace(str[i]))){
            symbolCount+=1;
        }
    }
    printf("Number of digit is:%d\n",digitCount);
    printf("Number of vowels:%d\n",vowelCount);
    printf("Number of symbol:%d\n",symbolCount);
    return 0;
}

// IP: any sentence with special symbol, vowels and numbers 
//  i.e. Hello#123
