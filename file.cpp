#include "file.h"

File::File(){
	permissions = vector<string> {"rwx", "rwx", "rwx"};

	time_t now = time(0);
	timeStamp = ctime(&now);
	
	name = "new file";
	parent = "root/";
	fileSize = 0;
}

string File::getName() const{
	return name;
}
