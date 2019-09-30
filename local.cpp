// local.cpp : Defines the entry point for the application.
//

#include "local.h"
#include <string>
#include <exception>
#include <fstream>
#include "parser.h"
#include "tree.h"
#include "staticSemantics.h"
#include "code.h"
//#include "code.cpp"


using namespace std;
void fileP(string, int, char**);

int main(int argc, char** argv) {
	try {
		Tree* root = parser(argc, argv);
		//cout << "tree works\n";
		StaticSemantics statsem(root);
		statsem.checkTree();

		Code codeGen(root);
		codeGen.generate();

		string code = codeGen.getCode();
		fileP(code, argc, argv);
	}
	catch (const std::exception& exc) {
		std::cerr << exc.what();
		return 1;
	}
	catch (...) {
		std::cerr << "An unknown exception was called.\n";
		throw;
	}

	return 0;
}


void fileP(string code, int argc, char** argv)
{
	string fname = "out.asm";
	if (argc == 2)
	{
		std::string ext = ".asm";
		fname = argv[1];
		fname.append(ext);
	}
	fstream file;
	file.open(fname, ios::out);
	file << code;
	file.close();
	cout << "File created: " << fname << "\n";
}