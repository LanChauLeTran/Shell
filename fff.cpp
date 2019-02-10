#include <sstream>
#include "folder.h"
#define BOLDBLUE "\033[1m\033[34m"  
#define RESET "\033[0m"

using namespace std;

int main(){
	Folder root;
	Folder* curDir = &root;
	  
	string input;
	bool cont = true;
	vector<string> parsed;
	string token;

	while(cont){
		cout << BOLDBLUE << curDir->getName() << RESET << "$ ";

		getline(cin, input);
		istringstream ss(input);
				 
		while(getline(ss, token, ' ')){
			parsed.push_back(token);
		}

		int inputSize = parsed.size();

		int i = 0;
		if(parsed[i] == "ls"){
			if(inputSize == 1){
				curDir->ls();
			}
			else if(inputSize == 2 && parsed[1] == "-l"){
				curDir->lsl();
			}
		}
		else if(parsed[i] == "cd"){
			if(inputSize == 2){
				cout << curDir->getName() << endl;
				
				if(parsed[1] != ".." && parsed[1] != "../"){
					curDir = curDir->cd(parsed[1]);
				}
				else if(parsed[1] == ".." || parsed[1] == "../"){
					curDir = curDir->getParent();
				}
			}	
		}
		else if(parsed[i] == "pwd"){
			cout << "call pwd function" << endl;
		}
		else if(parsed[i] == "rmdir"){
			
		}
		else if(parsed[i] == "mkdir"){
			if(inputSize < 2){
				cout << "mkdr: missing operand" << endl;
			}
			else{
				curDir->mkdir(parsed[1]);
			}
		}
		else if(parsed[i] == "rm"){
			cout << "call rm function" << endl;
		}
		else if(parsed[i] == "chmod"){
			cout << "call chmod function" << endl;
		}
		else if(parsed[i] == "touch"){
			if(inputSize < 2){
				cout << "touch: missing file operand" << endl;
			}
			else{
				for(i = 1; i < inputSize; i++){
					curDir->touch(parsed[i]);
				}
			}
		}

		parsed.clear();
		 
		if(input == "exit" || input == "quit")
			cont = false;
	}
	
	return 0;
}
