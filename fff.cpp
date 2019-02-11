#include <sstream>
#include "folder.h"
#include <cctype>
#include <stdio.h> 
#include <stdlib.h> 
#include <algorithm>
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
				if(parsed[1] != ".." && parsed[1] != "../"){
					curDir = curDir->cd(parsed[1]);
				}
				else if(parsed[1] == ".." || parsed[1] == "../"){
					if(curDir->getName() == "root"){
						cout << "cd: no parent exist in root" << endl;
					}
					else{
						curDir = curDir->getParent();
					}
				}
			}
			else if(inputSize == 1){
				curDir = &root;
			}
		}
		else if(parsed[i] == "pwd"){
			curDir->pwd();
		}
		else if(parsed[i] == "rmdir"){
			if(inputSize < 2) {
				cout << "rmdir: missing operand" << endl;
			}
			else{
				curDir->rmdir(parsed[1]);
			}
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
			if(inputSize < 2){
				cout << "rm: missing operand" << endl;
			}
			else{
				curDir->rm(parsed[1]);
			}
		}
		else if(parsed[i] == "chmod"){
			int permissionSize = parsed[1].size();
			if(inputSize == 3 && permissionSize == 3){
				curDir->chmod(parsed[2], parsed[1]);
			}
			else{
				cout << "chmod: invalid code: " << parsed[2] << endl;
			}
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
		else if(input == "exit" || input == "quit"){
			cont = false;
		}
		else{
			cout << "Invalid cmd" << endl;
		}

		parsed.clear();
	}
	
	return 0;
}
