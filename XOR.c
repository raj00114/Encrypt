#include<stdio.h>
#include<string.h>

void EncryptDecrypt(FILE* , FILE* , char[], short);
void modifyPassword( char[], char[], char[] ,short );

#define PASSWORD_MAX_LENGTH 30        
#define FILENAME_MAX_LENGTH 100
#define SECRET_KEY_LENGTH 30

/*password should not exceed 30 characters
file ca be find anywhere
password should not mismatch for encryption and decryption*/


int main(void)
{
    short choice = 1; //just to initialise

    FILE *inputFileptr, *outputFileptr;
    // +1 is for '\0' character
    char inputFile[FILENAME_MAX_LENGTH + 1], outputFile[FILENAME_MAX_LENGTH + 1 ];

    char password[PASSWORD_MAX_LENGTH+1];
    short passwordLen;

    //secret keys are choice of coder
    //use same secret key for encrypting and decrypting same file
    char SecretKey1[SECRET_KEY_LENGTH + 1] = "!$*(gi\%~.,&fuam4^<[}\\3em8os#*-"; //for other characters
    char SecretKey2[SECRET_KEY_LENGTH + 1] = "gR3$7(~G `.<_&@!\%1*9Azf2-+:;\"P"; //for uppercase cahracter
//these keys can changed

    while( choice != 3 )
    {
        printf ( "\n\n Welcome to Minor 1 \n\n" ) ;
        printf ( "*Please Select one of the following Options -:\n\n" ) ;
        printf ( "*Press 1 for Encryption\n*Press 2 for Decryption\n*Press 3 for Exit\n\n----->  " ) ;
        scanf ( "%hd" , &choice ) ;

        while ( choice > 3 || choice < 1 )
        {
            printf ( "Please Enter the Valid Choice\n" ) ;
            printf ( "* Press 1 for Encryption\n* Press 2 for Decryption\n*Press 3 for Exit\n\n----->  " ) ;
            scanf ( "%hd" , &choice ) ;
        }

        switch ( choice )
        {//encryption
        case 1:
        {
            printf ( "\nEnter the name of the file to be Encryted : " ) ;
            scanf("\n%[^\n]s",inputFile);

            printf ( "\nEnter the name of the file output file in which Encrypted data will be stored: " ) ;
            scanf("\n%[^\n]s",outputFile);

            inputFileptr = fopen ( inputFile, "rb");
            outputFileptr = fopen ( outputFile, "wb");

            if( inputFileptr == NULL || outputFileptr == NULL )
            {
                printf("\nError while opening file!");
                return 1;
            }

            printf( "\nEnter Password ( Length must be <= %d ) : ", PASSWORD_MAX_LENGTH ) ;
            scanf("\n%[^\n]s",password);
            //fgets(password, PASSWORD_MAX_LENGTH+1, stdin);
            passwordLen = strlen ( password ) ;

            modifyPassword( password, SecretKey1, SecretKey2, passwordLen);
            EncryptDecrypt(inputFileptr, outputFileptr, password, passwordLen );

            printf("Encrypted data has been stored in file %s\n\n", outputFile);
            break;
        }
        
		            //decryption
        case 2:
        {
            printf ( "\nEnter the name of the file to be Decrypted : " ) ;
            scanf("\n%[^\n]s",inputFile);

            printf ( "\nEnter the name of the output file in which decrypted text will be stored : " ) ;
            scanf("\n%[^\n]s",outputFile);

            inputFileptr = fopen ( inputFile, "rb");
            outputFileptr = fopen ( outputFile, "wb");

            if( inputFileptr == NULL || outputFileptr == NULL )
            {
                printf("\nError while opening file!");
                return 1;
            }

            printf( "\n Enter Password ( Length msut be <= %d ) : ", PASSWORD_MAX_LENGTH ) ;
            scanf("\n%[^\n]s",password);
            //fgets(password, PASSWORD_MAX_LENGTH+1, stdin);
            passwordLen = strlen ( password ) ;
            //changing password such that decryption becomes case sensitive
            //and changing even one character of password will fail in decrypting
            modifyPassword( password, SecretKey1, SecretKey2, passwordLen);
            EncryptDecrypt(inputFileptr, outputFileptr, password, passwordLen );

            printf("Decrypted data has been stored in file %s\n\n", outputFile);
            break;
        }

        case 3:
            break;
        }
    }
    return 0;
}
//Both encryption and decryption can be found here

void modifyPassword(char password[], char SecretKey1[], char SecretKey2[] , short passwordLen)
{
    int i = 0;

    while( password[i] != '\0' )
    {   //if password's character is uppercase letter then
        //it is ORed with corrosponding letter of SecretKey2 else with SecretKey1
        if ( 'A' <= password[i] && password[i] <= 'Z' )
            password[i] = password[i] | SecretKey2[i % SECRET_KEY_LENGTH] ;
        else
            password[i] = password[i] | SecretKey1[i % SECRET_KEY_LENGTH] ;
        i++;
    }
    
//It completely depends on user to select keys.

    int j;

    for ( i = 0 ; i < passwordLen ; ++i)
    {
        for (j = i + 1 ; j < passwordLen; ++j)
        {
            if (j == i)
                continue ;
            password[i] = password[i] & password[j];
        }
    }
}

//Determines the length of password as it should not exceed 30 characters

void EncryptDecrypt( FILE* inputptr, FILE* outputptr, char* password, short passwordLen )
{
    int tmp;
    short i = 0;
    while ( (tmp = fgetc(inputptr)) != EOF )
    {
        fputc(tmp ^ password[i], outputptr);
        i = ( i + 1 ) % passwordLen;
    }

    fclose(inputptr);
    fclose(outputptr);
}
