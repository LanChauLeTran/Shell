#ifndef CLASSES_H
#define CLASSES_H

#include <vector>
#include <string>
#include <ctime>

using namespace std;

class File{
	private:
		string name;
		string parent;
		vector<string> permissions;
		char* timeStamp;
		int fileSize;
	public:
		File();
		string getName() const;
};

#endif
