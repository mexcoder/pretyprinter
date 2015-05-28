#include <iostream>
#include <stdlib.h>
#include "htmlWriter.h"
#include "token.h"
#include <algorithm>
#include <string>

using namespace std;

htmlWriter::htmlWriter(char* fileName){

	tabs = 0;
	onelineTabs = 0;

	this->fileName = std::string(fileName) + ".html";

	file.open( this->fileName.c_str(), std::ofstream::trunc );

	printHeader();

}


htmlWriter::~htmlWriter(){

	this->end();

}

void htmlWriter::end(){

	printFooter();

	file.close();

	std::string cmd = "start " + this->fileName;

	system( cmd.c_str() );
}

void htmlWriter::addTab(){
	tabs++;
	file<<"            <br /><br /><div class=\"tab\">"<<endl;
}


void htmlWriter::clearTab(){
	tabs--;
	file<<"            </div><br />"<<endl;
}



void htmlWriter::printFooter(){

	file<<"        </div>"<<endl
		<<"    </body>"<<endl
		<<"</html>";

}


void htmlWriter::addToken(char* text, int tokenType){


	if(tokenType == T_EOL){
		file<<"<br />";
		return;
	}

	file<<"            <span class=T_"<<tokenType<<">"
		<<text
		<<"</span>";



}


void htmlWriter::printHeader(){

	file<<"<!doctype html>"<<endl
		<<"<html>"<<endl
		<<"    <head>"<<endl
		<<endl
		<<"        <style>"<<endl
		<<"            body{"<<endl
		<<"                background-color:black;"<<endl
		<<"                color:gray;"<<endl
		<<"            }"<<endl
		<<endl
		<<"            .T_"<<T_ID<<"{"<<endl
		<<"                color:springgreen;"<<endl
		<<"            }"<<endl
		<<endl
		<<"            .T_"<<T_OPERATOR<<"{"<<endl
		<<"                color:yellow;"<<endl
		<<"            }"<<endl
		<<endl
		<<"            .T_"<<T_STRING<<"{"<<endl
		<<"                color:red;"<<endl
		<<"            }"<<endl
		<<endl
		<<"            .T_"<<T_RESERVED<<"{"<<endl
		<<"                color:white;"<<endl
		<<"            }"<<endl
		<<endl
		<<"            .T_"<<T_COMMENT<<"{"<<endl
		<<"                color:forestgreen;"<<endl
		<<"            }"<<endl
		<<endl
		<<"            .T_"<<T_MACRO<<"{"<<endl
		<<"                color:dodgerblue;"<<endl
		<<"            }"<<endl
		<<endl
		<<"            .T_"<<T_CONSTANT<<"{"<<endl
		<<"                color:blueviolet;"<<endl
		<<"            }"<<endl
		<<endl
		<<"            .T_"<<T_TYPE<<"{"<<endl
		<<"                color:cornflowerblue;"<<endl
		<<"            }"<<endl
		<<endl
		<<"            .tab{"<<endl
		<<"                padding-left:4ch;"
		<<"            }"
		<<"        </style>"<<endl
		<<"    </head>"<<endl
		<<"    <body>"<<endl
		<<"        <div class=\"code\">"<<endl;
}