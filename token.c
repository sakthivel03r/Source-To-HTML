#include <stdio.h>
#include "html.h"

/* Extern Keyword used to Create Linkage between  other File*/
extern char State ;
extern char ch;
extern int Index ;
extern char Buffer[SIZE];
extern char colour ;

void Token_Identifier(Source * sptr)
{
    char Prev ;
    /* Check The Character and Update State & add character with Buffer then break */
    switch(ch)                                       
    {
        case '#' :
            State = PREPROCESSOR ;
            Buffer[Index++] = ch;                        
            break;

        case 'A' ... 'Z' :                                
        case 'a' ... 'z' :
            State = KEYWORD ;                              
            Buffer[Index++] = ch ;
            break;

        case '/' :
            Prev = ch ;
            ch = fgetc(sptr->Source_fptr);
            switch(ch)
            {
                case '/' :
                    Buffer[Index++] = Prev ;
                    Buffer[Index++] = ch;
                    State = SINGLELINE ;
                    break;

                case '*' :
                    Buffer[Index++] = Prev ;
                    Buffer[Index++] = ch;
                    State = MULTILINE ;
                    break;

                default :
                    fseek(sptr->Source_fptr,-2,SEEK_CUR);    //Set Cursor 2 head previous 
                    State = REGULAR_CHARACTER ;              //Update State with Regular character
            }
            break;

        case '0' ... '9' :
            Buffer[Index++] = ch;
            State = NUMBERCONSTANT ;
            break;

        case '\"' :
            Buffer[Index++] = ch;
            State = STRING ;
            break;

        case '\'' :
            Buffer[Index++] = ch;
            State = CHARACTERCONSTANT ;
            break;

        case '\n' :                                          //Character is New line then Directly print in Destination File
            fprintf(sptr->Dest_fptr,"\n");                   //Update State with Ideal 
            State = IDEAL ;
            break;

        default :                                   
            fseek(sptr->Source_fptr , -1 , SEEK_CUR);        //Set Cursor one point pervious and update state
            State = REGULAR_CHARACTER ;
            break;
    }

    Buffer[Index] = '\0';                                    //Add Null character in End of Buffer
}

void Source_To_Converstion(Source * sptr)
{
    /* Based on Input of Colour using fprintf print Buffer with Colour pattern of HTML*/
    switch(colour)
    {
        case BLUE   : fprintf(sptr->Dest_fptr ,"<span class=\"b\">%s</span>",Buffer);
                      break;

        case PURPLE : fprintf(sptr->Dest_fptr ,"<span class=\"p\">%s</span>",Buffer);
                      break;

        case GREEN  : fprintf(sptr->Dest_fptr ,"<span class=\"g\">%s</span>",Buffer);
                      break;

        case YELLOW : fprintf(sptr->Dest_fptr ,"<span class=\"y\">%s</span>",Buffer);
                      break;

        case CYAN   : fprintf(sptr->Dest_fptr ,"<span class=\"c\">%s</span>",Buffer);
                      break;

        case WHEAT  : fprintf(sptr->Dest_fptr ,"<span class=\"w\">%s</span>",Buffer);
                      break;

        case END    : fprintf(sptr->Dest_fptr ,"%s",Buffer);
                      break;
    }
}
