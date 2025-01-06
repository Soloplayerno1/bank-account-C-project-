#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 26

typedef struct{
    char name[MAX];
    char password[MAX];
    long balance;
}account;
//void Login();
void clear_input_buffer();
void Account();
void Login();
void inside_Account(account user);
void Deposite(account user);
void Withdraw(account user);


int main(){
    int choose = 0;
    account user; 
    while(choose != 3)
    {
        printf("_____________________________________\n");
        printf("1.Login\n2.Create account\n3.Exit\n");
        scanf("%d", &choose);
        clear_input_buffer();
        if(choose == 1)
        {
            Login();
        }
        if(choose == 2)
            Account();
        if(choose == 3)
            return 1;
    }
}

void inside_Account(account user){
    printf("Username: %s\n", user.name);
    printf("Current balance: %ld\n\n", user.balance);
    int choice = 0 ;
    while(choice!=5)
    {
        printf(" _______________\n");
        printf("|               |\n"); 
        printf("|1.Deposite     |\n");
        printf("|               |\n");
        printf("|2.Withdraw     |\n");
        printf("|               |\n");
        printf("|3.Transfer     |\n");
        printf("|               |\n");
        printf("|4.Check balance|\n");
        printf("|               |\n");
        printf("|5.Exit         |\n");
        printf("|_______________|\n\n\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            Deposite(user);
            break;
        case 2:
            Withdraw(user);
            break;
        case 4:
            FILE *file = fopen("user.txt", "r");
            char line[256];
            fgets(line,256,file);
            fgets(line,256,file);
            while(fgets(line,256,file)!=NULL)
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
                i+=2;
                int b = 0;
                char balance[50];
                while(line[i]!='\0')
                {
                    balance[b] = line[i];
                    b++; i++;
                }
                user.balance = atol(balance);
            }
        }
        fclose(file);
        printf("\n---------Infor account!-----------\n");
        printf("Username: %s\n", user.name);
        printf("Balance: %ld\n", user.balance);
        default:
            break;
        }
    }
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
    printf("___________\n\nAccount \"%s\" has been created\n____________\n", user.name);
    inside_Account(user);
}

void clear_input_buffer(){
    while(getchar()!='\n' && getchar() != EOF);
}


void Login(){
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
            i+=2;
            int b = 0;
            char balance[50];
            while(line[i]!='\0')
            {
                balance[b] = line[i];
                b++; i++;
            }
            user.balance = atol(balance);
            printf("\n\n____________________Login success_______________________.\n");
            fclose(f);
            inside_Account(user);
            return;
        }
    }
    printf("Incorrect username or password.\n");
    return ;
}


void update(account user){
    FILE *read = fopen("user.txt", "r");
    char line[256];
    FILE *write = fopen("write.txt", "w");
    fgets(line, 256, read);
    fputs(line,write);
    fgets(line, 256, read);
    fputs(line,write);
    while(fgets(line, 256, read)){
        char name[26];
        int i = 0;
        while(line[i]!=',')
        {
            name[i] = line[i];
            i++;
        }
        name[i] = '\0';
        if(!strcmp(name,user.name))
        {
            fprintf(write, "%s, %s, %ld\n", user.name, user.password, user.balance);
            continue;
        }
        fputs(line,write);
    }

    fclose(read);
    fclose(write);

    remove("user.txt");
    rename("write.txt", "user.txt");
}

void Deposite(account user){
    printf("\n---------------DEPOSITE------------------\n");
    long amount;
    printf("Amount: ");
    scanf("%ld", &amount);
    user.balance = user.balance + amount;

    update(user);
    printf("....Deposite succes!....\n");
}

void Withdraw(account user){
    printf("\n---------------WITHDRAW------------------\n");
    long amount;
    printf("Amount: \n");
    scanf("%ld", &amount);
    if(amount>user.balance)
    {
        printf("Withdraw failure!(Don't have enough money)\n");
        return;
    }
    user.balance = user.balance - amount;
    update(user);
    printf("--------< Withdraw success >--------");
    return;
}