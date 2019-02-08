#include <sstream>
#include <iostream>
#include "classes.cpp"

using namespace std;

int main(){
	Folder root;
	string curDir = root.getName();
	string input;
	bool cont = true;
	vector<string> parsed;
	string token;

	while(cont){
		getline(cin, input);
		istringstream ss(input);
				 
		while(getline(ss, token, ' ')){
			parsed.push_back(token);
		}

		int i = 0;
		if(parsed[i] == "ls"){
			if(parsed.size() == 2 && parsed[++i] == "-l"){
				cout << "call Ls -l function" << endl;
			}
			else{
				cout << "call ls" << endl;
			}
		}
		else if(parsed[i] == "cd"){
			cout << "call cd function" << endl;
		}
		else if(parsed[i] == "pwd"){
			cout << "call pwd function" << endl;
		}
		else if(parsed[i] == "mkdir"){
			cout << "call mkdir function" << endl;
		}
		else if(parsed[i] == "rmdir"){
			cout << "call rmdir function" <<endl;
		}
		else if(parsed[i] == "rm"){
			cout << "call rm function" << endl;
		}
		else if(parsed[i] == "chmod"){
			cout << "call chmod function" << endl;
		}
		else if(parsed[i] == "touch"){
			cout << "call touch function" << endl;
			File testFile;
		}

		parsed.clear();
		 
		if(input == "exit" || input == "quit")
			cont = false;
	}
	
	return 0;
}
