#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "html.h"

/* Using Extern keyword to create linkage with Other File */
extern char * Macro[] ;
extern char State ;
extern int Index ;
extern char ch;
extern char Buffer[SIZE];
extern char colour;

const char * Declaration[] = {"char","int","float","double","signed","unsigned","short","long","const","volatile","auto","registor","static","extern","struct","union","enum","typedef","void","FILE"};
const char * ControlFlow[] = {"for","while","do","goto","break","continue","if","else","switch","case","default","return","sizeof"};

Result Is_Constant(char ch)
{
    if(isalnum(ch) || ch == '.' || ch == '_')                    //Checking Character is isalnum or dot or underscore then return SUCCESS
        return SUCCESS ;

    else                                                         //If not present return FAILURE
        return FAILURE ; 
}

Result Is_FormateSpecifier(char ch)
{
    if(strchr("abcdefginpsuxzl%#*.",ch) != NULL)                //Checking Character present in string or Not
        return SUCCESS ;                                         //present return SUCCESS or return FAILURE

    else
        return FAILURE ;
}

void AngularBracket(char Buffer[] , char ch)
{
    if(ch == '<')                                               //Checking character is less than then copy string "&lt;" in string
        strcpy(Buffer, "&lt;");

    else
        strcpy(Buffer, "&gt;");                                 //else store string "&gt;" in string 

    Index = Index + 4;                                          //Update index with index plus 4 (character of string "&gt;" -> 4)
}

Result Preprocessor(Source * sptr)
{
    do
    {
        if(ch == '\n')                                          //Check Character is New line & break the loop
            break;

        if(Buffer[0] == '#' && (ch == '<' || ch == '\"'))       //Check Buffer first character is # and current Character is < or " & break the loop
            break;

        else if(ch == '<' || ch == '>')                         //Cheak the Character is < or >
            AngularBracket(&Buffer[Index],ch);                  //Function call to add "&lt;" or "&gt;" 

        else
            Buffer[Index++] = ch ;                              //add character into Buffer and increment Index count

        if(ch == ' ' || ch == '\t')                             //Character is whitespace or Tab break the loop
            break;

    }while((ch = fgetc(sptr->Source_fptr)) != EOF);             //Running loop upto Character not equal to EOF

    if(ch == '\n' || ch == '<' || ch == '\"')                   //Check character is newline or < or (")                                            
        ungetc(ch , sptr->Source_fptr);                         //Throw back the character into File Again

    if(Buffer[0] == '#' || isalpha(Buffer[0]))                  //Check the Buffer First Character is # or digit 
    {
        colour = BLUE ;                                         //Update Colour with Blue & State with Preprocessor
        State = PREPROCESSOR ;
    }

    else                                                        //If Not then update colour with PURPLE & state with IDEAL
    {
        colour = PURPLE ;  
        State = IDEAL ;
    }

    return SUCCESS ;                                            //return SUCCESS
}

Result KeyWord(Source * sptr)
{
    char Size_D = sizeof(Declaration) / sizeof(Declaration[0]); //Find the Size of Decalaration 2D array
    char Size_CF = sizeof(ControlFlow) / sizeof(ControlFlow[0]);//Find the Size of ControllFlow 2D array
    char i = 0, Prev = 0; colour = END ; State = IDEAL ;

    do
    {
        if(Is_Constant(ch) == FAILURE)                          //Check the character is Not Constant break the loop
            break;

        Buffer[Index++] = ch;                                   //add Character into Buffer & increment the index

    }while((ch = fgetc(sptr->Source_fptr)) != EOF);             //Running loop upto character not equal to EOF

    Buffer[Index] = '\0';
    if(ch != EOF)                                               //Check the Character is Not equal to EOF 
        ungetc(ch , sptr->Source_fptr);                         //throw back the character to File again

    for(char i = 0 ; i < Size_D ; i++)                          //Running Loop upto Size of Decalaration 2D array
    {
        if(!strcmp(Buffer , Declaration[i]))                    //Check Buffer string & Decalartion array string is matching
        {
            colour = GREEN ;                                    //Update Colour with GREEN and return SUCCESS
            return SUCCESS ;
        }
    }

    for(char i = 0 ; i < Size_CF ; i++)                         //Running Loop upto Size of ControlFlow 2D array
    {
        if(!strcmp(Buffer , ControlFlow[i]))                    //Check Buffer string & Control Flow array string is Matching
        {
            colour = YELLOW ;                                   //Update Colour with Yellow and return SUCCESS
            return SUCCESS ;
        }
    }

    while(Macro[i])                                             //Running Loop upto macro of i reach NULL 
    {
        if(!strcmp(Buffer,Macro[i++]))                          //Check Buffer string 2D array of Macro string is Matching
        {
            colour = PURPLE ;                                   //Update Colour with Purple
            break;
        }
    }

    return SUCCESS ;                                            //return SUCCESS
}

Result Single_Line_Comment(Source * sptr)
{
    do
    {
        if(ch == '\n')                                          //Check character is New Line and break the loop
            break;

        Buffer[Index++] = ch;                                   //Add character in Buffer

    }while((ch = fgetc(sptr->Source_fptr)) != EOF);             //Running loop upto Character is Not equal to EOF

    if(ch != EOF)                                               //Check the character is Not equal to EOF
        ungetc(ch , sptr->Source_fptr);                         //Throw back the character into File again

    colour = CYAN ;                                             //Update Colour with Cyan
    State = IDEAL;                                              //Updtae State with Ideal
    return SUCCESS ;                                            //return SUCCESS
}

Result Multi_Line_Comment(Source * sptr)
{
    char Prev = 0;
    do
    {
        Buffer[Index++] = ch;                                   //Add Character into Buffer & increment the Index
        if(Prev == '*' && ch == '/')                            //Check Current character is backslah & previous character is star & break the loop
            break;

        Prev = ch ;                                             //Update previous with Current character

    }while((ch = fgetc(sptr->Source_fptr)) != EOF);             //running loop upto Character not equal to EOF

    colour = CYAN ;                                             //Update coloue with CYAN
    State = IDEAL;                                              //Update State with IDEAL
    return SUCCESS ;                                            //return SUCCESS
}

Result NumberConstant(Source * sptr)
{
    do
    {
        if(Is_Constant(ch) == FAILURE )                         //Check the Function return type is Failure & break the loop
            break;

        Buffer[Index++] = ch ;                                  //add the character into Buffer & increment the Index

    }while((ch = fgetc(sptr->Source_fptr)) != EOF);             //Running loop upto Character Not equal to EOF

    if(ch != EOF)                                               //Check the character is Not equal to EOF
        ungetc(ch , sptr->Source_fptr);                         //Throw back the character into file again

    colour = PURPLE ;                                           //Uapdate coloue with PURPLE & state with Ideal 
    State = IDEAL ;
    return SUCCESS ;                                            //return SUCCESS to the Function call
}

Result String(Source * sptr)
{
    char Prev = 0 , percentage = 0; colour = PURPLE ;

    do
    {
        if(ch == '%')                                           //Check the Character is % & increment the percentage 
            percentage++;

        if(ch == '\\' && Buffer[0] != '\\')                     //check the Current Character is backslash & Buffer first character is backslash 
            break;                                              //break the loop

        else if(ch == '%' && Buffer[0] != '%')                  //Chek character is % & Buffer first character not equal to % then break the Loop
            break;

        else if(ch == '<' || ch == '>')                         //Check the Character is angular bracket
            AngularBracket(&Buffer[Index],ch);

        else if(percentage)                                     //check the percentage is Nonzero
        {
            // Check the character is formate specifier & character is & or percentage modulo by 2 is 1 then add in Buffer
            if(Is_FormateSpecifier(ch) && (ch == '%' || percentage % 2))
                Buffer[Index++] = ch;

            else
            {
                if(ch == '\"')                                  //Check the character is " & throw back character into Source File 
                    ungetc(ch , sptr->Source_fptr);
                colour = WHEAT ;                                //update colour with WHEAT & break the loop
                break;
            }
        }

        else
            Buffer[Index++] = ch ;                              //add character into Buffer

        if(ch == '\"' && Prev != '\\')                          //Check Current character is " and previous character is not equal to backslash
        {
            State = IDEAL ;                                     //update state with IDEAL & return SUCCESS
            return SUCCESS ;
        }

        else if(Prev == '\\')                                   //Check previous character is backslash & break the loop
        {
            colour = WHEAT ;  
            break;
        }

        Prev = ch;                                              //Update previous characeter with Current Character

    }while((ch = fgetc(sptr->Source_fptr)) != EOF);

    if(ch != EOF && ch != '\"' && Prev != '\\')                 //check character is Not equal to EOF and " and backslash
        ungetc(ch , sptr->Source_fptr);                         //throw back the current character into Source File

    State = STRING ;                                            //Update State with String
    return SUCCESS ;                                            //return SUCCESS
}

Result CharacterConstant(Source * sptr)
{
    char Prev = 0 ; colour = PURPLE ;
    do
    {
        if(ch == '<' || ch == '>')                              //Check the Charater is Angular bracket & call the Function
            AngularBracket(&Buffer[Index],ch);

        else  
            Buffer[Index++] = ch;                               //add character into Buffer & increment the Index

        if(Prev == '\\')                                        //Check the previous Character is backslash & update colour with WHEAT
            colour = WHEAT ;

        if(ch == '\'' && Prev != '\\')                          //Check Current character is ' and previous character is not equal to backslash
            break;                                              //break the loop

        Prev = ch ;                                             //store current character to previous character

    }while((ch = fgetc(sptr->Source_fptr)) != EOF);             //running loop upto character is Not equal to EOF

    State = IDEAL ;                                             //Update State with Ideal & return SUCCESS
    return SUCCESS ;
}

Result Regular_Character(Source * sptr)
{
    if(ch == '<' || ch == '>')                                  // Check the Character Angular bracket
    {
        AngularBracket(&Buffer[Index],ch);                      //Function call to add string "&gt;" or "&lt;"
        Index++;
    }

    else
        Buffer[Index++] = ch;                                   //Add the character into Buffer
    colour = END;                                               //update colour with END , State with IDEAL
    State = IDEAL ;
    return SUCCESS ;                                            //return SUCCESS
}
