#ifndef FOLDER_H
#define FOLDER_H

#include <vector>
#include <string>
#include <ctime>

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
		string getParent() const;
		
		void setFiles(const File& f);
};

#endif
