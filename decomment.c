#include <stdio.h>
#include <stdlib.h>
/*********************************
 *Enum with all states of the DFA*
 *********************************/
enum States
{
    NORMAL, SLASH, STARBG, STARED, DQUOTE, SQUOTE, BSLASH, DQ_BSLASH, SQ_BSLASH, S_BSLASH 
};
/************************************************
 *Set of functions to handle each of the states *
 ************************************************/

/*Function for the normal state*/
void normalStateHandler(int character,enum States *state){
    if(character  =='/'){
        *state = SLASH;
    }
    else if(character  == '"'){
        *state = DQUOTE;
        putchar(character);
    }
    else if(character  == '\''){
        *state = SQUOTE;
        putchar(character);
    }
    else if(character  == '\\'){
        *state = BSLASH;
    }
    else{
        *state = NORMAL;
        putchar(character);
    }
}
/*Function for the slash state*/
void slashStateHandler(int character,enum States *state){
    if(character == '*'){
        *state = STARBG;
        putchar(' ');
    }
    else if(character == '/'){
        *state = SLASH;
        putchar(character);
    }
    else{
        *state = NORMAL;
        putchar('/');
        putchar(character);
    }
}
/*Function for the starbg state*/
void starbgStateHandler(int character,enum States *state){
    if(character == '*'){
        *state = STARED;
    }
    else if(character == '\\'){
        *state = S_BSLASH;
    }
    else{
        *state = STARBG;
    }
}
/*Function for the stared state*/
void staredStateHandler(int character,enum States *state){
    if(character == '/'){
        *state = NORMAL;
    }
    else if(character == '*'){
        *state = STARED;
    }
    else{
        *state = STARBG;
    }

}
/*Function for the dquote state*/
void dquoteStateHandler(int character,enum States *state){
    if(character == '"'){
        *state = NORMAL;
        putchar(character);
    }
    else if(character == '\\'){
        *state = DQ_BSLASH;
    }
    else{
        *state = DQUOTE;
        putchar(character);
        
    }

}
/*Function for the squote state*/
void squoteStateHandler(int character,enum States *state){
    if(character == '\''){
        *state = NORMAL;
        putchar(character);
    }
    else if(character == '\\'){
        *state = SQ_BSLASH;
    }
    else{
        *state = SQUOTE;
        putchar(character);
    }

}
/*Function for the bslash state*/
void bslashStateHandler(int character,enum States *state,int *line){
    if(character =='n'){
        *state = NORMAL;
        putchar('\n');
        (*line)++;
    }
    else{
        *state = NORMAL;
        putchar('\\');
        putchar(character);
    }
}
/*Function for the dq_bslash state*/
void dq_bslashStateHandler(int character,enum States *state,int *line){
    if(character =='n'){
        putchar('\n');
        (*line)++;
    }
    else{
        putchar('\\');
        putchar(character);
    }
    *state = DQUOTE;
}
/*Function for the sq_bslash state*/
void sq_bslashStateHandler(int character,enum States *state,int *line){
    if(character =='n'){
        putchar('\n');
        (*line)++;
    }
    else{
        putchar('\\');
        putchar(character);
    }
    *state = SQUOTE;
}
/*Function for the s_bslash state*/
void s_bslashStateHandler(int character,enum States *state,int *line){
    if(character =='n'){
        putchar('\n');
        (*line)++;
    }
    else{
        putchar('\\');
        putchar(character);
    }
    *state = STARBG;
}

/********************************************************
 *Function to check the state of the DFA and take action*
 ********************************************************/
int checkState(int character ,enum States *state, int *line){
    if(character =='\n'){ /*Increment line number*/
            (*line)++;
    }
    if(*state == NORMAL){
        /*Handle NORMAL state*/
        normalStateHandler(character,state);
    }
    else if(*state == SLASH){
         /*Handle SLASH state*/
         slashStateHandler(character,state);
    }
    else if(*state == STARBG){
         /*Handle STARBG state*/
         starbgStateHandler(character,state);
    }
    else if(*state == STARED){
         /*Handle STARED state*/
         staredStateHandler(character,state);
    }
    else if(*state == DQUOTE){
         /*Handle DQUOTE state*/
         dquoteStateHandler(character,state);
    }
    else if(*state == SQUOTE){
         /*Handle SQUOTE state*/
          squoteStateHandler(character,state);
    }
    else if(*state == BSLASH){
         /*Handle BSLASH state*/
         bslashStateHandler(character,state,line);
    }
    else if(*state == DQ_BSLASH){
         /*Handle DQ_BSLASH state*/
         dq_bslashStateHandler(character,state,line);
    }
    else if(*state == SQ_BSLASH){
         /*Handle SQ_BSLASH state*/
         sq_bslashStateHandler(character,state,line);
    }
    else if(*state == S_BSLASH){
         /*Handle S_BSLASH state*/
         s_bslashStateHandler(character,state,line);
    }
}
/******************************************************************
 *Decomment Program, it takes code form a file or standard input  *
 *and returns the decommented version of the text to the standard * 
 *output.                                                         *
 *****************************************************************/
int main(int argc, char *argv[]){
    FILE  *file;
    /*Initialize the enum*/
    enum States state;
    state=NORMAL;
    /*Initialize line number at 0*/
    int line = 0;
    /*character variable*/
    int character;
    /*If no additional arguments are given, the code will be read from stdin*/
    if(argc==1) {
        /*Decomment the input*/
		while ((character=getchar())!=EOF){
            checkState(character,&state, &line);
        }
	} 
    /*If a file has been specified, the code will be read form the file*/
    else if(argc==2) {
        /*Open the file as readonly*/
		file = fopen(argv[1], "r");
        /*Handle file input error*/
		if(file == NULL) {
            fprintf(stderr, "Cannot open the file\n");
            exit(-1);
		}
        /*Decomment the input*/
        while ((character=getc(file))!=EOF){
            checkState(character,&state, &line);
        }
        /*close file stream*/
        fclose(file);
    }   
  /* If the loop finshed at starbg or stared state, we know there is unterminated comment*/
        if(state == STARBG || state == STARED){
            /*Print error line to stderr*/
            fprintf(stderr, "Error: line %d: unterminated comment\n",line);
            exit(-1);     
  }
  return 0;
}