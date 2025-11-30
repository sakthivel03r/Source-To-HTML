/* 

Name   : Sakthivel R
Tittle : Source To HTML
Date   : 18 - 10 - 2025

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "html.h"

char State;
int Index ;
char ch;
char Buffer[SIZE];
char colour ;

int Open_File(char * argv[] , Source * sptr)
{
    system("clear");
    sptr->Source_Fname = argv[1];                        //Store Argument 1 in Structure Variable
    printf(O"INFO : "E"File "B"< %s > "E"Opening\n" ,argv[1]);
    if((sptr->Source_fptr = fopen(argv[1],"r")) == NULL) //Checking File is Open or Not
    {
        printf(R "INFO : "E"File "B"< %s >"E" Not Open\n" , argv[1]);
        return FAILURE ;
    }

    printf(G"INFO : "E"File "B"< %s >"E" Open Successfully\n" , argv[1]); 
    sptr->Dest_Fname = malloc(strlen(argv[1]) + 6);      //Create Memory Dynamically by Malloc

    if(!sptr->Dest_Fname)                                //Check File is Open or Not by checking variable Hold NULL or not
    {
        printf(R "INFO : "E"Memory Not Created For Variable "B"< %s >"E"\n",sptr->Dest_Fname);
        return FAILURE ;
    }

    char FileName[30];
    strcpy(FileName , argv[1]);                         //Copy Source File Name in one Variable
    strcpy(FileName , strtok(FileName , "."));          //Separate File Name with with extenstion and Store in variable
    sprintf(sptr->Dest_Fname , "%s.html" , FileName);   //Store Destination File Name in Structure with Extension of .html

    printf(G"INFO : "E"Destination File "B"< %s >"E" Created Successfully\n" , sptr->Dest_Fname);
    printf(O"INFO : "E"File "B"< %s > "E"Opening\n" ,sptr->Dest_Fname);

    if((sptr->Dest_fptr = fopen(sptr->Dest_Fname , "w")) == NULL)  //Checking Destination File is Open or Not
    {
        printf(R "INFO : "E"File "B"< %s >"E" is Not Open\n" , sptr->Dest_Fname);
        return FAILURE ;
    }

    printf(G"INFO : "E"File "B"< %s > "E"Open Successfully\n" ,sptr->Dest_Fname);
    return SUCCESS ;                                    //return Success
}

void HTML_HEAD(FILE * fp)
{
    fprintf(fp,"<!DOCTYPE html>\n""<html lang=\"en-US\">\n");
    fprintf(fp,"<head>\n""<title>Source2HTML</title>\n");
    fprintf(fp,"\t<meta charset=\"UTF-8\">\n");
    fprintf(fp,"<link rel=\"stylesheet\" href=\"colour.css\">\n");
    fprintf(fp,"</head>\n""<body>\n""<pre>\n");

    printf(G"INFO : "E"Head of the "B"< HTML >"E" added to the "B"< Destination File >"E" Successfully\n");
}

void HTML_TAIL(FILE * fp)
{
    fprintf(fp ,"\n\t</pre>\n");
    fprintf(fp,"</body>\n</htmlsource>\n");

    printf(G"INFO : "E"Tail of "B"< HTML >"E" addedd to "B"< Destination File >"E" Successfully\n");
}

void loading(char string[])
{
    int len = strlen(string);
    for (int i = 0; i < len; i++)
    {
        printf(G "\r%*s%.*s"E, len - i, "", i + 1, string);
        fflush(stdout);
        usleep(300000);
    }
}

void Token_State(Source * sptr)
{
    // Find the State and Call respective Function do to the Sepecific Task
    while((ch = fgetc(sptr->Source_fptr)) != EOF)      //Running loop upto Character is Not equal to EOF
    {
        switch(State)
        {
            case IDEAL :                             
                Token_Identifier(sptr);
                break;

            case PREPROCESSOR :                  
                if(Preprocessor(sptr))
                    return ;

            case KEYWORD :
                if(KeyWord(sptr))
                    return ;

            case SINGLELINE :
                if(Single_Line_Comment(sptr))
                    return ;

            case MULTILINE :
                if(Multi_Line_Comment(sptr))
                    return ;

            case NUMBERCONSTANT :
                if(NumberConstant(sptr))
                    return ;

            case STRING :
                if(String(sptr))
                    return ;

            case CHARACTERCONSTANT :
                if(CharacterConstant(sptr))
                    return ;

            case REGULAR_CHARACTER :
                if(Regular_Character(sptr))
                    return ;
        }
    }

    State = STATE_EOF;                //Update State with Stata_Eof when loop end
}

int main(int argc , char * argv[])
{
    if(argc != 2)                     //Checking Argument Count is Not equal to 2 & return FAILURE
    {
        printf(T"Usage :"E" %s "B"<"E" File.c "B">"E"\n" , argv[0]);
        return FAILURE ;              
    }

    Source source;                    //Create Structure variable
    Open_File(argv , &source);        //Function call to Open file and store FILE address in structure 
    HTML_HEAD(source.Dest_fptr);      //Function call to add HTML header
    State = IDEAL ;                   //Update State with IDEAL
    printf(T"INFO : "E"Token Separation "O"Started\n"E);

    do
    {
        Token_State(&source);         //Function call to Token Identification
        Buffer[Index] = '\0';         //Store Buffer last character NULL 
        if(ch == EOF)                 //check ch is equal to -1 & break the loop
            break;

        Source_To_Converstion(&source);//Function call to Creating Token
        Index = 0;                     //Update Index with 0
        if(State == STRING)            //Check State holding enum STRING
            Buffer[0] = ch;            //update Buffer first Character with Current character holding in variable ch 

        else
            Buffer[Index] = '\0';      //Store First Character has NULL

    }while(State != STATE_EOF);        //Running loop upto State not equal to State Eof

    loading("Just a Seconds To Finesh");
    printf(G"\rINFO : "E"Token Separation "O"Completed\n"E);
    HTML_TAIL(source.Dest_fptr);       //Function call to add tail of HTML
    printf(G"INFO : Source "B"C"E" "G"To"E" "B"HTML"E" "G"Converstion Done Successfully\n"E);
    loading("Loading Destination File");
    printf(T"\rINFO : "E"Destination File -> "B"< %s >\n"E,source.Dest_Fname);
    return SUCCESS ;                   //return SUCCESS 
}
