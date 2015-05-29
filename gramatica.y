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
%token T_SEMICOLON
%token T_COMA
%token T_EQUAL

%%

TYPE:			  T_TYPE
				| TYPE T_TYPE
				;

DECLARACION: 	  TYPE T_ID
				| TYPE T_ID T_EQUAL
				| DECLARACION T_COMA T_ID
				;

OPERATION:		  T_ID T_OPERATOR T_ID
				| T_ID T_OPERATOR OPERATION

ALL: T_ID {;}
;
%%
