#include <iostream>
#include "htmlWriter.h"
#include "token.h"
#include "gramatica.tab.h"

using namespace std;

extern "C" int yylex();

/*c wrapers*/
extern "C" void add_tab();
extern "C" void clear_tab();
extern "C" void recv_token(char*,int);//wraper for the class method
extern "C" FILE * yyin;

htmlWriter* w;

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

		cout<<"leyendo instrucciones del archivo \""<<argv[1]<<"\""<<endl;
	}


	w = new htmlWriter(argv[1]);
	
	yylex();

	delete w;

}

extern "C" void recv_token(char* token,int tokenType){
	cout<<"got token: "<<token<<" of type "<<tokenType<<endl;
	w->addToken(token, tokenType);

}

extern "C" void add_tab(){

	w->addTab();

}

extern "C" void clear_tab(){

	w->clearTab();

}