%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int yylval;

    enum yytokentype
    {
        KEYWORD = 36,
        OPERATOR = 40,
        DELIMITER = 80,
        STRINGS = 100,
        CHARACTERS = 101,
        IDENTIFIER = 102,
        NUM = 103
    };
%}

line    \n
blank   [ \t]
blanks  {blank}+
letter  [A-Za-z_]
digit   [0-9]
dlmt    [#$@]
id      {letter}({letter}|{digit})*
num     [+\-]?{digit}+(\.{digit}+)?(e[+\-]?{digit}+)?
charac  ['].[']


%%


{blanks}    ;
"/*".*"*/"  ;
"//".*      ;
("\"")(.)*("\"")  return STRINGS;
{charac}    return CHARACTERS;

"auto" 		{yylval = 1 ; return KEYWORD;}
"break" 	{yylval = 2 ; return KEYWORD;}
"case" 		{yylval = 3 ; return KEYWORD;}
"char" 		{yylval = 4 ; return KEYWORD;}
"const" 	{yylval = 5 ; return KEYWORD;}
"continue" 	{yylval = 6 ; return KEYWORD;}
"default" 	{yylval = 7 ; return KEYWORD;}
"do" 		{yylval = 8 ; return KEYWORD;}
"double" 	{yylval = 9 ; return KEYWORD;}
"else" 		{yylval = 10 ; return KEYWORD;}
"enum" 		{yylval = 11 ; return KEYWORD;}
"extern" 	{yylval = 12 ; return KEYWORD;}
"float" 	{yylval = 13 ; return KEYWORD;}
"for" 		{yylval = 14 ; return KEYWORD;}
"goto" 		{yylval = 15 ; return KEYWORD;}
"if" 		{yylval = 16 ; return KEYWORD;}
"int" 		{yylval = 17 ; return KEYWORD;}
"long" 		{yylval = 18 ; return KEYWORD;}
"register" 	{yylval = 19 ; return KEYWORD;}
"return" 	{yylval = 20 ; return KEYWORD;}
"short" 	{yylval = 21 ; return KEYWORD;}
"signed" 	{yylval = 22 ; return KEYWORD;}
"sizeof" 	{yylval = 23 ; return KEYWORD;}
"static" 	{yylval = 24 ; return KEYWORD;}
"struct" 	{yylval = 25 ; return KEYWORD;}
"switch" 	{yylval = 26 ; return KEYWORD;}
"typedef" 	{yylval = 27 ; return KEYWORD;}
"union" 	{yylval = 28 ; return KEYWORD;}
"unsigned" 	{yylval = 29 ; return KEYWORD;}
"void" 		{yylval = 30 ; return KEYWORD;}
"volatile" 	{yylval = 31 ; return KEYWORD;}
"while" 	{yylval = 32 ; return KEYWORD;}
"\\t"       {yylval = 33; return KEYWORD;}
"\\n"       {yylval = 34; return KEYWORD;}
"main" 	    {yylval = 35; return KEYWORD;}

"+" 		{yylval = 41 ;return OPERATOR;}
"-" 		{yylval = 42 ;return OPERATOR;}
"*" 		{yylval = 43 ;return OPERATOR;}
"/" 		{yylval = 44 ;return OPERATOR;}
"%" 		{yylval = 45 ;return OPERATOR;}
"=" 		{yylval = 46 ;return OPERATOR;}
"&" 		{yylval = 47 ;return OPERATOR;}
"|" 		{yylval = 48 ;return OPERATOR;}
"^" 		{yylval = 49 ;return OPERATOR;}
"!" 		{yylval = 50 ;return OPERATOR;}
"<" 		{yylval = 51 ;return OPERATOR;}
">" 		{yylval = 52 ;return OPERATOR;}
"+=" 		{yylval = 53 ;return OPERATOR;}
"-=" 		{yylval = 54 ;return OPERATOR;}
"*=" 		{yylval = 55 ;return OPERATOR;}
"/=" 		{yylval = 56 ;return OPERATOR;}
"%=" 		{yylval = 57 ;return OPERATOR;}
"&&" 		{yylval = 58 ;return OPERATOR;}
"||" 		{yylval = 59 ;return OPERATOR;}
"==" 		{yylval = 60 ;return OPERATOR;}
"!=" 		{yylval = 61 ;return OPERATOR;}
"<=" 		{yylval = 62 ;return OPERATOR;}
">=" 		{yylval = 63 ;return OPERATOR;}
"++" 		{yylval = 64 ;return OPERATOR;}
"--" 		{yylval = 65 ;return OPERATOR;}
"<<" 		{yylval = 66 ;return OPERATOR;}
">>" 		{yylval = 67 ;return OPERATOR;}
"&=" 		{yylval = 68 ;return OPERATOR;}
"|=" 		{yylval = 69 ;return OPERATOR;}
"^=" 		{yylval = 70 ;return OPERATOR;}
"<<=" 		{yylval = 71 ;return OPERATOR;}
">>=" 		{yylval = 72 ;return OPERATOR;}
"->" 		{yylval = 73 ;return OPERATOR;}

"#" 		{yylval = 81 ; return DELIMITER;} 
"$" 		{yylval = 82 ; return DELIMITER;} 
"@" 		{yylval = 83 ; return DELIMITER;} 
"[" 		{yylval = 84 ; return DELIMITER;} 
"]" 		{yylval = 85 ; return DELIMITER;} 
"{" 		{yylval = 86 ; return DELIMITER;} 
"}" 		{yylval = 87 ; return DELIMITER;} 
"(" 		{yylval = 88 ; return DELIMITER;} 
")" 		{yylval = 89 ; return DELIMITER;} 
"?" 		{yylval = 90 ; return DELIMITER;} 
":" 		{yylval = 91 ; return DELIMITER;} 
"." 		{yylval = 92 ; return DELIMITER;} 
";"         {yylval = 93 ; return DELIMITER;} 
"," 		{yylval = 94 ; return DELIMITER;} 


{id}        {return IDENTIFIER;}
{num}       {return NUM;}


%%

int main()
{
    yyin = fopen("demo.c", "r");

    FILE * fp;
	fp = fopen("tokens.txt", "w");


    int token_type;

    fputs("CONTENT\t\t\tTOKEN_TYPE\n", fp);
    while(token_type = yylex())
    {
        //fprintf(fp, "token_type: %d", token_type);
        fprintf(fp, "%s\t\t\t%d\n", yytext, token_type);
    }
	fclose(fp);
}

int yywrap()
{
	return 1 ;
}
