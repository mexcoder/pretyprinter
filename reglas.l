%option noyywrap
%option case-insensitive

	#include "token.h"
	#include "gramatica.tab.h"
	void recv_token(char*,int);
	void save_token(char*,int);
	void add_tab();
	void clear_tab();
	void join_tokens(int);

Reservada asm|auto|bool|break|case|catch|char|class|const|const_cast|continue|default|delete|do|double|dynamic_cast|else|enum|explicit|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|operator|private|protected|public|register|reinterpret_cast|return|short|signed|sizeof|static|static_cast|struct|switch|template|this|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|while|\(|\)|NULL
Tipo char|short|int|long|bool|float|double|unsigned
Operador sizeof|typeid|delete|delete|typeof|new|<<=|>>=|->\*|::\*|>>|<=|>=|!=|==|&&|\|\||<<|&=|\|=|\^=|->|\.\*|::|!!|\?:|::|\+\+|--|\+=|-=|\/=|%=|<|>|!|~|&|\||\^|=|\*|\.|,|\+|-|\/|%|\?|:|\{|\}|\[|\]|\;
Macro #[^ ]*
Comentario \n?(\/\/.*)\n
	//|\/\*(.|[\r\n\/])*
String \"(\\\"|[^"])*\"|\'(\\'|[^'])\'
Constante -?(0x[0-9a-fA-F]+|([[:digit:]]+(\.[[:digit:]]+)?))
id [[:alpha:]][[:alnum:]_]*

%x macro
%x multiLineC
%s s_for

%%

	/*for bison*/

{Comentario} recv_token(yytext,T_COMMENT); //return T_COMMENT;

\/\*[*\/]* save_token(yytext,T_COMMENT);BEGIN(multiLineC);
<multiLineC>(\*\/)\n? save_token(yytext,T_COMMENT);join_tokens(T_COMMENT);BEGIN(INITIAL);//return T_ANY;
<multiLineC>[^*\/]* save_token(yytext,T_COMMENT);


	/*for save_token( yytext, T_RESERVED );
	\( save_token( yytext, T_RESERVED );
	\) save_token( yytext, T_RESERVED );*/

\}; clear_tab();recv_token(yytext,T_OPERATOR);recv_token("",T_EOL);recv_token("",T_EOL);
\{ recv_token(yytext,T_OPERATOR);add_tab();
\} clear_tab();recv_token(yytext,T_OPERATOR);recv_token("",T_EOL);recv_token("",T_EOL);

for recv_token(yytext,T_RESERVED);BEGIN(s_for);
<s_for>; {recv_token( yytext, T_OPERATOR );}
<s_for>\) {recv_token( yytext, T_RESERVED );BEGIN(INITIAL);}

; {recv_token( yytext, T_OPERATOR );recv_token("",T_EOL);}
	/*, save_token( yytext, T_OPERATOR );
	= save_token( yytext, T_OPERATOR );*/


{Macro} recv_token(yytext,T_MACRO); BEGIN(macro);
<macro>[^\n]*\n  recv_token(yytext,T_STRING);BEGIN(INITIAL);

{Constante} recv_token(yytext,T_CONSTANT);
{String} recv_token(yytext, T_STRING);
{Tipo} recv_token(yytext, T_TYPE);
{Reservada} recv_token(yytext, T_RESERVED);
{id} recv_token(yytext, T_ID);
{Operador} recv_token(yytext, T_OPERATOR);

\n {}
. //


	/*legacy*

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
	<*>\n //consumir, para que no me atasque la consola*/


%%

