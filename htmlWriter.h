#include <fstream>

class htmlWriter{

	protected: 
	
		int tabs;
		int onelineTabs;
		int signature;
		std::string fileName;
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