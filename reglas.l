%option noyywrap
%option case-insensitive
	#include "token.h"
	#include "gramatica.tab.h"
	void recv_token(char*,int);
	void add_tab();
	void clear_tab();

Reservada asm|auto|bool|break|case|catch|char|class|const|const_cast|continue|default|delete|do|double|dynamic_cast|else|enum|explicit|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|operator|private|protected|public|register|reinterpret_cast|return|short|signed|sizeof|static|static_cast|struct|switch|template|this|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|while|\(|\)|NULL
Tipo char|short|int|long|bool|float|double|unsigned
Operador sizeof|typeid|delete|delete|typeof|new|<<=|>>=|->\*|::\*|>>|<=|>=|!=|==|&&|\|\||<<|&=|\|=|\^=|->|\.\*|::|!!|\?:|::|\+\+|--|\+=|-=|\/=|%=|<|>|!|~|&|\||\^|=|\*|\.|,|\+|-|\/|%|\?|:|\{|\}|\[|\]|;
Macro #[^ ]*
Comentario (\/\/.*)
String \"(\\\"|[^"])*\"|\'.*\'
Constante (0x)?[[:digit:]]*
id [[:alpha:]][[:alnum:]_]*

%x multiLineC
%x macro
%x macro2
%%

	/*for bison*/

= return(T_EQUAL);
, return(T_COMA);
; return(T_SEMICOLON);
\( return(T_L_PARENTESIS);
\) return(T_R_PARENTESIS);
for return(T_FOR);


	/*legacy*/

; recv_token(yytext,T_OPERATOR);recv_token("",T_EOL);

\{ recv_token(yytext,T_OPERATOR);add_tab();
\} clear_tab();recv_token(yytext,T_OPERATOR);recv_token("",T_EOL);recv_token("",T_EOL);

{Comentario} recv_token(yytext,T_COMMENT);recv_token(yytext,T_EOL);

\/\*.*\*\/ recv_token(yytext,T_COMMENT);
\/\*.* recv_token(yytext,T_COMMENT);BEGIN(multiLineC);
<multiLineC>\*\/ recv_token(yytext,T_COMMENT);BEGIN(INITIAL);
<multiLineC>[^*\n]* recv_token(yytext,T_COMMENT);
<multiLineC>\n recv_token("",T_EOL);

{String} recv_token(yytext,T_STRING);
{Constante} recv_token(yytext,T_CONSTANT);
{Tipo} recv_token(yytext,T_TYPE);
{Operador} recv_token(yytext,T_OPERATOR);

{Macro} recv_token(yytext,T_MACRO);BEGIN(macro);
<macro>{String} recv_token(yytext,T_STRING);recv_token("",T_EOL);BEGIN(INITIAL);
<macro>\< recv_token("&lt;",T_STRING);BEGIN(macro2);
<macro2>\> recv_token("&gt;",T_STRING);recv_token("",T_EOL);BEGIN(INITIAL);
<macro2>[^>]* recv_token(yytext,T_STRING);

{Reservada} recv_token(yytext,T_RESERVED);

{id} recv_token(yytext,T_ID);

. recv_token(yytext,T_UNDEF);
<*>\n //consumir, para que no me atasque la consola


%%

