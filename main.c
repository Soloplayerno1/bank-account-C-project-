#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//void Login();
void clear_input_buffer();
void Account();
void Log();


typedef struct{
    char name[26];
    char password[20];
    int money;
}account;

int main(){
    Log();
}

void Log(){
    int choose; 
    printf("1.Login\n2.Create account\n");
    scanf("%d", &choose);
    clear_input_buffer();
    // if(choose == 1)
    //     Login();
    if(choose == 2)
        Account();
}

void get_User_Name(char* username, FILE *name){
    printf("User name: ");
    fgets(username, 26, stdin);
    int i = 0;
    while(username[i]!='\0')
    {
        if(username[i] == '\n')
            username[i] = '\0';
        i++;
    }
        char n[256];
    
    while(fgets(n,256, name)!=NULL)
    {
        int j=0;
        while(n[j]!='\0')
        {
            if(n[j] == '\n')
                n[j] = '\0';
            j++;
        }
        if(!strcmp(username,n))
        {
            printf("This name has already exist\n");
            fseek(name, 0, SEEK_SET);
            get_User_Name(username, name);
        }
    }
}

void Account(){ 
    account user;
    FILE* name = fopen("name.txt", "a+");
    get_User_Name(user.name, name);
    printf("Password: ");
    scanf("%s", &user.password);
    fprintf(name, "%s\n", user.name);
    printf("Create success.");
    fclose(name);
}

void clear_input_buffer(){
    while(getchar()!='\n' && getchar() != EOF);
}
