#include <iostream>
#include "htmlWriter.h"
#include "token.h"
#include "gramatica.tab.h"
#include <vector>

#pragma clang diagnostic ignored "-Wc++11-extensions"

using namespace std;

extern "C" int yylex();
extern "C" int yyparse();

/*c wrapers*/
extern "C" void print_tokens();
extern "C" void add_tab();
extern "C" void clear_tab();
extern "C" void join_tokens(int);
extern "C" void recv_token(char*,int);//wraper for the class method
extern "C" void save_token(char*,int);
extern "C" FILE * yyin;

struct stoken{
	string token;
	int tokenType;
};

htmlWriter* w;
vector<stoken> tokenList;

bool debug = false;

int main(int argc, char *argv[]){

	for(int x =0;x<1;x++);


	if(argc == 1){ //sin parametros
		cout<<"se requiere el archivo";
		return -1;
		
	}
	else{//el primer parametro deberia ser el archivo

		yyin = fopen(argv[1],"r");

		if(yyin == NULL)
		{
			cout<<"error al leer el archivo";
			return -1;
		}

		cout<<"leyendo el archivo \" "<<argv[1]<<"\""<<endl;
	}


	w = new htmlWriter(argv[1]);
	
	yylex();
	//yyparse();

	delete w;

}

extern "C" void recv_token(char* token,int tokenType){
	//cout<<"got token: "<<token<<" of type "<<tokenType<<endl;
	w->addToken(token, tokenType);

}

extern "C" void add_tab(){

	w->addTab();

}

extern "C" void clear_tab(){

	w->clearTab();

}

extern "C" void save_token(char* t,int st){
	//cout<<"(store) got token: "<<t<<" of type "<<st<<endl;
	stoken tokenItem;
	
	tokenItem.token = t;
	tokenItem.tokenType = st;

	tokenList.push_back( tokenItem );

}

void print_tokens(){

	for(auto it : tokenList)
	{
		recv_token( (char*) it.token.c_str(), it.tokenType);
	}

	tokenList.clear();

}

extern "C" void join_tokens(int T_type){

	string res = "";

	for(auto it : tokenList)
	{
		res += it.token;
	}

	recv_token( ( char * )res.c_str() , T_type);

}