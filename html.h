#ifndef HTML_H
#define HTML_H

#define SIZE 1024

/* Colour Code */
#define G "\033[1;92m"
#define R "\033[1;91m"
#define B "\033[1;94m"
#define T "\033[38;2;0;206;209m"
#define Y "\033[38;2;255;215;0m"
#define O "\033[38;2;255;140;0m"
#define E "\033[0m"

/* Input and Output File Name & File Pointers*/
typedef struct
{
    char *Source_Fname;
    char *Dest_Fname;
    FILE *Source_fptr;
    FILE *Dest_fptr;

}Source ;

/* Token States */
typedef enum
{
    FAILURE ,
    SUCCESS ,
    IDEAL ,
    PREPROCESSOR ,
    SINGLELINE ,
    MULTILINE ,
    KEYWORD ,
    STRING ,
    NUMBERCONSTANT ,
    CHARACTERCONSTANT ,
    REGULAR_CHARACTER ,
    STATE_EOF

}Result;

/* Enum for Colour */
typedef enum
{
    BLUE ,
    PURPLE ,
    GREEN ,
    YELLOW ,
    WHEAT ,
    CYAN ,
    END

}Code;

/* Identify Token State , Token Identifier , Convert to HTML*/
void Token_State(Source *);
void Token_Identifier(Source *);
void Source_To_Converstion(Source *);

/* Token Making Functions */
Result Preprocessor(Source *);
Result KeyWord(Source * sptr);
Result Single_Line_Comment(Source *);
Result Multi_Line_Comment(Source *);
Result NumberConstant(Source *);
Result String(Source *);
Result CharacterConstant(Source *);
Result Regular_Character(Source *);

#endif
