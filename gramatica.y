%{
	
	int printf ( const char * format, ... );
	extern void  recv_token(char*,int);
	extern int yylex();
    void yyerror(const char *s) { printf("ERROR: %s\n", s); }
%}

%token T_ID
%token T_OPERATOR
%token T_STRING
%token T_RESERVED
%token T_COMMENT
%token T_MACRO
%token T_CONSTANT
%token T_TYPE

%token T_FOR
%token T_L_PARENTESIS
%token T_R_PARENTESIS
%token T_L_BRA
%token T_R_BRA
%token T_SEMICOLON
%token T_COMA
%token T_EQUAL
%token T_EOL

%token T_COMENT_START
%token T_COMENT_END
%token T_COMENT_CONTENT

%token T_UNKNOWN
%token T_ANY

%%

com: T_COMMENT {;}
   | com T_COMMENT {;}
   | com error{recv_token("",T_EOL); printf("found comment block\n");} 

MACRO: T_MACRO {;}
 	 | T_MACRO MACRO {;}
 	 | MACRO error { recv_token("<BR />",T_STRING); printf("found macro block\n");exit( 0);}
     ;
	
any: T_ANY
   | any T_ANY
   ;

%%
