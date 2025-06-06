
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    #define MAXINPUTSIZE 32
    #define RESERVEDAMOUNT 48 // Can keep this the same for each binary
    #define RESERVEDAMOUNT2 73
    #define NAMELENGTH 32 // Always the same for each binary
    #define CANARYLENGTH 16 // Always the same for each binary

    #define TRUE 1
    #define FALSE 0
    #define PASSWORDLENGTH 32
    #define BINARYNAME "binary_40.txt"
    char* password = "ca06b160b60f11b767740612f4a67dbc";


    
    // Put the elements of this shirt in random order
    typedef struct _CustomShirt{
	 char reservedForFutureUse[RESERVEDAMOUNT];
	char * hackerName;
	} CustomShirt;

    typedef struct _TweetShirt{
        char reservedForFutureUse[RESERVEDAMOUNT2];
        char canaryName[16];
    } TweetShirt;

    CustomShirt * s1;
    CustomShirt * s2;
    TweetShirt * ts;

    char canary[16] = "SWlUskGjFCKxodWL"; // make this random
    
    int getInput(int length, char * buffer){
    memset(buffer, 0, length);
    int count = 0;
    char c;
    while((c = getchar()) != '\n' && !feof(stdin)){
        if(count < (length-1)){
            buffer[count] = c;
            count++;
        }
    }
    buffer[count] = '\x00';
    return count+1;
    }

    char getMenuSelection(){
        char input[2]; 
        getInput(2, input);
        return input[0];
    }

    void gracefulExit(){
        free(s1->hackerName);
        free(s2->hackerName);
        free(s1);
        free(s2);
        exit(0);
    }

    void writeHackerName(CustomShirt * cs){
        printf("\nHow long is your hacker name? ");
        fflush(stdout);
        char tmpIndex[10];
        getInput(10, tmpIndex); 
        int length = atoi(tmpIndex); 
        printf("\nPlease enter the hacker name: ");
        fflush(stdout);
        fgets(cs->hackerName, length, stdin);
        return;
    }

    void checkCanary(){
        for(int i = 0; i < CANARYLENGTH; i++){
            if (ts->canaryName[i]!=canary[i]){
                printf("Error: Mismatch in canary at index %d\n", i);
                printf("       TweetShirt canary value is %c\n", ts->canaryName[i]);
                printf("       Canary value is %c\n", canary[i]);
                exit(0);
            }
        }
    }

    void writeShirt(){
        printf("\nPlease enter the shirt you want to edit (1 or 2): ");
        fflush(stdout);
        char tmpIndex[10];
        getInput(10, tmpIndex); 
        int index = atoi(tmpIndex); 
        if (index == 1){
            writeHackerName(s1);
            checkCanary();
        } else if(index == 2) {
            writeHackerName(s2);
        } else{
            puts("Error: invalid index.");
            exit(0);
        }
        puts("\nYour shirt name has been updated.\n");
    }

    void readShirt(){
        printf("\nPlease enter the shirt you want to read (1 or 2): ");
        fflush(stdout);
        char tmpIndex[10];
        getInput(10, tmpIndex); 
        int index = atoi(tmpIndex); 
        if (index == 1){
            printf("\nShirt 1 reads: %s\n", s1->hackerName);
        } else if (index == 2){
            printf("\nShirt 2 reads: %s\n", s2->hackerName);
        } else{
            puts("Error: invalid index. Program will exit.");
            exit(0);
        }
    }

    void displayMenu(){
        puts("Menu Options ");
        puts("-------------");
        puts("1) Edit shirt");
        puts("2) View shirt");
        puts("3) Exit");
        return;
    }

    void handleMenuSelection(char selection){
        if(selection == '1'){
            writeShirt();
        }
        else if(selection == '2'){
            readShirt();
        }
        else if(selection == '3'){
            puts("Goodbye!");
            gracefulExit();
        }
        else{
            printf("Error: invalid selection.\n");
            exit(0);
        }
        return;
    }

    void initializeShirts(){
        s1 = malloc(sizeof(CustomShirt));
        memset(&s1->reservedForFutureUse, 0, RESERVEDAMOUNT);
        s1->hackerName = malloc(NAMELENGTH);
        ts = malloc(sizeof(TweetShirt));
        memset(&ts->reservedForFutureUse, 0, RESERVEDAMOUNT2);
        memcpy(&ts->canaryName, canary, 16);
        s2 = malloc(sizeof(CustomShirt));
        memset(&s2->reservedForFutureUse, 0, RESERVEDAMOUNT);
        s2->hackerName = malloc(NAMELENGTH);
        return;
    }

    char equalArrays(char a[], char b[], int size){
        for(int i = 0; i < size; i++){
            if(a[i]!=b[i]){
                return FALSE;
            }
        }
        return TRUE;
    }

    void printBinary(){
        char c;
        FILE * f;
        f = fopen(BINARYNAME, "r");
        if(f == NULL){
            puts("Error reading hex of binary");
            exit(0);
        }
        c = fgetc(f);
        while (c != EOF){
            printf("%c", c);
            c = fgetc(f);
        }
        fclose(f);
        return;
    }

    int password_is_correct(char* user_input){
        return equalArrays(password, user_input, PASSWORDLENGTH-1);
    }

    void runChallenge(){
        initializeShirts();
        puts("    *** Custom Shirt Awareness Week 2021 ***\n");
        puts("    Hello! Please use this program to request an official");
        puts("CSAW 2021 T-shirt. Some say our shirts are for the birds, but");
        puts("really only some are for the birds. Our most popular shirts");
        puts("can be custom ordered with your hacker name on them.");
        puts("    Please order up to two shirts. During the ordering process");
        puts("you may view or edit a shirt as much as you like.\n");
        while(1){
            displayMenu();
            printf("Enter your choice (1-3): ");
            fflush(stdout);
            char selection = getMenuSelection();
            handleMenuSelection(selection);
        }
        return;
    }

    // This is the template but we want the generator for this code to use command-line arguments to populate these fields:
    // 1. DOCUMENT
    int main(int argc, char **argv){
    puts("Welcome to the AEG challenges!");
    char user_input[PASSWORDLENGTH];
    puts("Input password to continue:");
    printf("> ");
    fflush(stdout);
    fgets(user_input, PASSWORDLENGTH+2, stdin);
    if (password_is_correct(user_input)){
        puts("Correct password! :)");
        puts("Here is the binary that is currently running on this box: ");
        puts("-------------------------------------------------------------------");
        printBinary();
        puts("-------------------------------------------------------------------");
        puts("\nProceeding to the challenge...\n");
        fflush(stdout);
        runChallenge();
    }else{
        printf("Incorrect password. :(");
    }
    return 0;
    }    
    