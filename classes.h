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

class Folder{
	private:
		string parent;
		string name;
		string permissions;
		string timeStamp;
		vector<File> files;
		vector<Folder> folders;

	public:
		Folder(): name("root/") {}
		void setFiles(const File& f);
		string getParent() const;
		string getName() const;
};

#endif
