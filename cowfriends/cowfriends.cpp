/*
This program is designed to display your message as being said by the cow
and all his friends.

Goals:
 - Get all the other display types
  - from here: /usr/local/share/cows
  - If that fails, use fallback list
 - Run the command for each.

*/
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std; // i am harmful

// cowpaths for homebrew, linux, macports
const char* cowPaths[] = {"/usr/local/opt/cowsay/share/cows", "/usr/share/cowsay/cows", "/opt/local/share/cowsay/cows"};
int cowPathsCount = 3;
const std::string dotCow = ".cow";


bool endsWithDotCow(std::string fName) {
	if(fName.size() > dotCow.size()) {
		return fName.compare(fName.size() - dotCow.size(), dotCow.size(), dotCow) == 0;
	}
}


vector<string> getFriends(DIR* cowdir) {
	vector<string> friends;
	struct dirent *entry;
	while((entry = readdir(cowdir)) != NULL) {
		auto fName = entry->d_name;
		if(endsWithDotCow(fName)) {
			friends.push_back(entry->d_name);
		} else {
			cout << "didn't end with .cow: " << fName << endl;
		}
		
	}
	closedir(cowdir);
	return friends;
}

vector<string> getCows() {
	DIR *cowdir;
	for(int i = 0; i < cowPathsCount; i++) {
		if((cowdir = opendir(cowPaths[i])) != NULL) {
			return getFriends(cowdir);
		}
	}
	cout << "Error: couldn't find a valid cowpath!" << endl;
	exit(1);
}

void say(string f, string text) {
	std::string cmd = "cowsay -f ";
	cmd.append(f);
	cmd.append(" ");
	cmd.append(text);
	system(cmd.c_str());
}

int main(int argc, char *argv[]) {
	auto friends = getCows();
	string text = "";
	if(argc <= 1) {
		// need to get stdin for this
	} else {
		for(int i = 1; i < argc; i++) {
			text.append(argv[i]);
			if(i != argc-1) {
				text.append(" ");
			}
			
		}
	}
	for(string i : friends) {
		say(i, text);
	}
}
