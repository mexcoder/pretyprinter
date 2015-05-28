%token T_ID
%token T_OPERATOR
%token T_STRING
%token T_RESERVED
%token T_COMMENT
%token T_MACRO
%token T_CONSTANT
%token T_TYPE

%%
ALL: T_ID {;}
;
%%
