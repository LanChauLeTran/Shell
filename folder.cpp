#include "folder.h"
#include <algorithm>
#include <map>
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

Folder* Folder::getParent(){
	if(parent != nullptr){
		return parent;
	}
}

void Folder:: touch(const string& fileName){
	bool exist = false;
	for (auto &i: files){
		if(i.getName() == fileName){
			exist = true;
			i.updateTime();
		}
	}
	if(!exist){
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
		cout << "mkdir: '" << dirName << "' directory already exists." << endl;
	}
	else{
		auto newFolder = new Folder();
		newFolder->parent = this;
		newFolder->name = dirName;
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
			 << '\t' << BOLDBLUE << i->getName() << RESET 
			 << endl;
	}
}

Folder* Folder::cd(const string& name){
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
	else{
		cout << "bash: cd: " << name << ": no such directory" << endl;
		return this;
	}
}

void Folder::pwd(){
	string path = "";
	Folder* cur = this;
	while(cur->parent != nullptr){
		path = cur->name + "/" +  path;
		cur = cur->parent;
	}
	path = "/" + cur->name + "/" + path;
	cout << path << endl;
}

void Folder::rmdir(const string& dir){
	bool exist = false;
	for (int i = 0; i < folders.size(); i++){
		if(folders[i]->getName() == dir){
			exist = true;
			delete folders[i];
			folders.erase(folders.begin() + i);
		}
	}
	if(!exist){
		cout << "rmdir: directory does not exist" << endl;
	}
	/*
	auto foundIt = find_if(folders.begin(), folders.end(), [dir](auto curDir) {
		return curDir->name == dir;
	});
	if(foundIt == folders.end()) {
		cout << "rmdir: directory does not exist" << endl;
		return;
	}
	delete *foundIt;
	folders.erase(foundIt);*/
}

void Folder::rm(const string& target){
	bool exist = false;
	for (int i = 0; i < files.size(); i++){
		if(files[i].getName() == target){
			files.erase(files.begin() + i);
			exist = true;
		}
	}
	if(!exist){
		cout << "rm: cannot remove '" << target << "': No such file" << endl;
	}

/*
	bool exist = false;
	for(auto i = files.begin(); i != files.end(); i++){
		if(i->getName() == target){
			files.erase(i);
			exist = true;
		}
	}
	if(!exist){
		cout << "rm: cannot remove '" << target << "': No such file" << endl;
	}*/
}

void Folder::chmod(const string& obj, const string& perm){
	map<string, string> permValues;
	permValues.insert(pair<string, string>("0", "---"));
	permValues.insert(pair<string, string>("1", "--x"));
	permValues.insert(pair<string, string>("3", "-wx"));
	permValues.insert(pair<string, string>("4", "r--"));
	permValues.insert(pair<string, string>("5", "r-x"));
	permValues.insert(pair<string, string>("6", "rw-"));
	permValues.insert(pair<string, string>("7", "rwx"));	

	string newPerm = "";
	bool fileExist = false;
	bool folderExist = false;
	int indexOfFile;
	int indexOfFolder;
	

	for (int i = 0; i < perm.size(); i++){
		if(perm[i] < '0' || perm[i] > '7'){
			cout << "chmod: invalid mode: " << obj << endl;
			return;
		}
		else{
			string find = "";
			find = perm[i];
			newPerm = newPerm + permValues.find(find)->second;
		}
	}

	for (int i =  0; i < files.size(); i++){
		if(files[i].getName() == obj){
			fileExist = true;
			indexOfFile = i;
		}
	}
	for (int i = 0; i < folders.size(); i++){
		if(folders[i]->getName() == obj){
			folderExist = true;
			indexOfFolder = i;
		}
	}

	if(!fileExist && !folderExist){
		cout << "chmod: invalid mode: " << obj << endl;
		return;
	}
	else if(fileExist){
		files[indexOfFile].setPerm(newPerm);
		files[indexOfFile].updateTime();
	}
	else if(folderExist){
		folders[indexOfFolder]->setPerm(newPerm);
		folders[indexOfFolder]->updateTime();
	}
}

void Folder::setPerm(const string& newPerm){
	permissions = newPerm;
}

void Folder::updateTime(){
	time_t now = time(0);
	char* temp = ctime(&now);
	temp[strlen(temp)-1] = '\0';
	timeStamp = temp;
}