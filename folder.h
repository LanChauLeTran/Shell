#ifndef FOLDER_H
#define FOLDER_H

#include "file.h"

class Folder{
	private:
		Folder* parent;
		string name;
		string permissions;
		string timeStamp;
		int folderSize;
		vector<File> files;
		vector<Folder* > folders;
	
	public:
		Folder(): name("/"), parent(nullptr) {}
		Folder(const string& folderName);
		~Folder();

		string getName() const;
		string getPerm() const;
		string getTime() const;
		int getSize() const;

		void touch(const string& fileName);
		void mkdir(const string& dirName);
		void ls() const;
		void lsl() const;
		//Folder* cd(const string)
};

#endif
