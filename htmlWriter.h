#include <fstream>
#include <tr1/unordered_map>

class htmlWriter{

	protected: 

		std::string nl2br(std::string);	
		std::string scapeTag(std::string);
		std::string replaceAll(std::string, std::string,std::string);
		int tabs;
		int onelineTabs;
		std::tr1::unordered_map< int, int > signature;
		std::string fileName;
		std::string orgFileName;
		std::ofstream file;
		void printHeader();
		void printFooter();
		void openFile();
		void closeFile();
		std::string getSignature();


	public:

		htmlWriter(char*);
		~htmlWriter();
		void addToken(char*,int);
		void end();
		void addTab();
		void clearTab();

};