#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//void Login();
void clear_input_buffer();
void Account();
bool Login();
void Log();

#define MAX 26

typedef struct{
    char name[MAX];
    char password[MAX];
    long balance;
}account;

int main(){
    Log();
}

void Log(){
    int choose; 
    printf("1.Login\n2.Create account\n");
    scanf("%d", &choose);
    clear_input_buffer();
    if(choose == 1)
        Login();
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
    fprintf(name, "%s\n", user.name);
    fclose(name);

    FILE *f = fopen("user.txt", "a+");
    printf("Password: ");
    scanf("%s", &user.password);
    printf("Deposite: ");
    scanf("%ld", &user.balance);
    while(user.balance < 10){
        printf("Deposite must be larger or at least euqal to 10\n");
        printf("Deposite: ");
        scanf("%ld", &user.balance);
    }
    fprintf(f, "\n%s, %s, %ld", user.name, user.password, user.balance);
    fclose(f);
    printf("Create success.");
}

void clear_input_buffer(){
    while(getchar()!='\n' && getchar() != EOF);
}


bool Login(){
    account user;
    printf("User name: ");
    fgets(user.name, 26, stdin);
    user.name[strcspn(user.name, "\n")] = '\0';
    printf("Password: ");
    scanf("%s", &user.password);
    FILE *f = fopen("user.txt", "r");
    char line[256];
    fgets(line,sizeof(line), f);
    fgets(line,sizeof(line), f);
    while(fgets(line,256,f)!=NULL)
    {
        int i = 0;
        char username[26], password[26];

        while(line[i]!=',')
        {
            username[i] = line[i];
            i++;
        }
        username[i] = '\0';
        i+=2; 
        int p=0;
        while(line[i]!=',')
        {
            password[p] = line[i];
            i++; p++;
        }
        password[p] = '\0';
        if(!strcmp(user.name, username) && !strcmp(user.password, password))
        {
            printf("Login success.");
            return true;
        }
    }
    fclose(f);
    printf("Incorrect username or password.");
    return false;
}