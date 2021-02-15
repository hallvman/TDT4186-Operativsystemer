/* This is a simple skeleton for a lex scanner */
/* It reads and echoes all input until "end" is read */

%{
#include <stdio.h>
enum { END = 256 };
%}

%%

end  { return (END); }
.    { printf("%c", yytext[0]); }

%%

int main(void) {
  int token;

  while (1) {
    token = yylex();

    if (token == END)
      break;
  } 
  printf("\nBye!\n");
  return 0;
}

