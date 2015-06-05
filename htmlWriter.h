#include <fstream>

class htmlWriter{

	protected: 

		std::string nl2br(std::string);	
		std::string scapeTag(std::string);
		std::string replaceAll(std::string, std::string,std::string);
		int tabs;
		int onelineTabs;
		int signature;
		std::string fileName;
		std::string orgFileName;
		std::ofstream file;
		void printHeader();
		void printFooter();
		void openFile();
		void closeFile();


	public:

		htmlWriter(char*);
		~htmlWriter();
		void addToken(char*,int);
		void end();
		void addTab();
		void clearTab();

};