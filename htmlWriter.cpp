#include <iostream>
#include <stdlib.h>
#include "htmlWriter.h"
#include "token.h"
#include "gramatica.tab.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string htmlWriter::scapeTag(string str){

	str = replaceAll(str,"<","&lt;");
	str = replaceAll(str,">","&gt;");

	return str;
}

string htmlWriter::replaceAll(string str ,string from, string to){

	if(from.empty())
        return str;

    //remove \r
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }

    return str;

}


string htmlWriter::nl2br(string str){

	str = replaceAll(str,"\r","");

	str = replaceAll(str,"\n","<br />");

	return str;
}

htmlWriter::htmlWriter(char* fileName){

	tabs = 0;
	onelineTabs = 0;

	string tmp = fileName;
	
	this->orgFileName = tmp.substr(tmp.find_last_of("/\\")+1);

	//tmp = tmp.substr(0,tmp.find_last_of("/\\"));



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
	file<<"        <br />"<<endl
	    <<"        <br />"<<endl
	    <<"        <div class=\"tab\">"<<endl;
}


void htmlWriter::clearTab(){
	tabs--;
	file<<"        </div>"<<endl
	    <<"        <br />"<<endl;
}



void htmlWriter::printFooter(){

	file<<"        </div>"<<endl
		<<"        <div id=\"header\">"<<endl
		<<"			   <div id=\"filename\">"<<endl
		<<"                <span>Archivo:</span>"<<endl
		<<"                <span class=\"attrib\">"<<this->orgFileName<<"</span>"<<endl
		<<"                <span>("<<endl
		<<"                    <span class=\"attrib\">"<<this->signature<<"</span>"<<endl
		<<"                 )<span>"<<endl
		<<"            </div>"<<endl
		<<"            <span id=\"close\" onClick=\"alert('cerrar ventana')\">X</span>"<<endl
		<<"        </div>"<<endl
		<<"    </body>"<<endl
		<<"</html>";

}


void htmlWriter::addToken(char* text, int tokenType){

	signature+=tokenType;


	if(tokenType == T_EOL){
		file<<"    <br />"<<endl;
		return;
	}

	file<<"            "
		<<"<span class=T_"<<tokenType<<">"
		<<nl2br( scapeTag( text ) )
		<<"</span>"<<endl;



}


void htmlWriter::printHeader(){

	file<<"<!doctype html>"<<endl
		<<"	<html>"<<endl
		<<"    <head>"<<endl
		<<endl
		<<"        <style>"<<endl
		<<"            body{"<<endl
		<<"                background-color:black;"<<endl
		<<"                color:gray;"<<endl
		<<"                font-family:monospace;"<<endl
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
		<<"            }"<<endl
		<<endl
		<<"            div.code {"<<endl
		<<"              margin-top: 30px;"<<endl
		<<"            }"<<endl
		<<endl
		<<"            div#header {"<<endl
		<<"              position: fixed;"<<endl
		<<"              top: 0;"<<endl
		<<"              left: 0;"<<endl
		<<"              right: 0;"<<endl
		<<"              background-color: rgb(10, 89, 23);"<<endl
		<<"              box-shadow: 0px -6px 20px #c0c0c0;"<<endl
		<<"              padding:5px 10px;"<<endl
		<<"            }"<<endl
		<<"            #close {"<<endl
		<<"              top: 0;"<<endl
		<<"              position: absolute;"<<endl
		<<"              right: 0;"<<endl
		<<"              cursor: pointer;"<<endl
		<<"              padding: 5px;"<<endl
		<<"              color: bisque;"<<endl
		<<"              background-color: darkcyan;"<<endl
		<<"            }"<<endl
		<<"            #header > div {"<<endl
		<<"              display: inline-block;"<<endl
		<<"              color: darkseagreen;"<<endl
		<<"            }"<<endl
		<<"            span.attrib {"<<endl
		<<"              color: blanchedalmond;"<<endl
		<<"            }"<<endl
		<<"        </style>"<<endl
		<<"    </head>"<<endl
		<<"    <body>"<<endl
		<<"        <div class=\"code\">"<<endl;
}