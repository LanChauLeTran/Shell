#include "folder.h"
#define BOLDBLUE "\033[1m\033[34m"  
#define RESET "\033[0m"

Folder::Folder(const string& folderName){
	name = folderName;
	permissions = "rwxrwxrwx";
	parent = this;
	time_t now = time(0);
	char* temp = ctime(&now);
	temp[strlen(temp)-1] = '\0';
	timeStamp = temp;
	folderSize = 1024;
}

Folder::~Folder(){
	for (auto i: folders){
		delete i;
	}
}

string Folder::getName() const{
	return name;
}

string Folder::getPerm() const{
	return permissions;
}

string Folder::getTime() const{
	return timeStamp;
}

int Folder::getSize() const{
	return folderSize;
}

void Folder:: touch(const string& fileName){
	bool exist = false;
	for (auto i: files){
		if(i.getName() == fileName)
			exist = true;
	}
	if(exist){
		//update time stamp
	}
	else{
		files.push_back(File(fileName));
	}
}

void Folder::mkdir(const string& dirName){
	bool exist = false;
	for (auto i: folders){
		if(i->getName() == dirName)
			exist = true;
	}
	if(exist){
		//update time stamp
	}
	else{
		auto newFolder = new Folder();
		newFolder->parent = this;
		newFolder->name = dirName;

		cout << "newFolder name: " << newFolder->getName() << endl;
		cout << "parent name: " << newFolder->parent->name << endl;

		newFolder->permissions = "rwxrwxrwx";
		time_t now = time(0);
		char* temp = ctime(&now);
		temp[strlen(temp)-1] = '\0';
		newFolder->timeStamp = temp;
		newFolder->folderSize = 1024;
		folders.push_back(newFolder);
	}
}

void Folder::ls() const{
	for (auto i: files){
		cout << i.getName() << '\t';
	}
	for (auto i: folders){
		cout << BOLDBLUE << i->getName() << RESET << '\t';
	}
	cout << endl;
}

void Folder::lsl() const{
	for (auto i: files){
		cout << "-" << i.getPerm() 
			 << '\t' << i.getSize()
			 << '\t' << i.getTime()
			 << '\t' << i.getName()
			 << endl;
	}
	for (auto i: folders){
		cout << "d" << i->getPerm()
			 << '\t' << i->getSize()
			 << '\t' << i->getTime()
			 << '\t' << i->getName()
			 << endl;
	}
}

Folder* Folder::cd(const string& name) const{
	bool exist = false;
	Folder* found;
	for (auto i: folders){
		if(i->getName() == name){
			exist = true;
			found = i;
		}
	}
	if(exist){
		return found;
	}
}