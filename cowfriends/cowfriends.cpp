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

using namespace std; // i am harmful

// cowpaths for homebrew, linux, macports
const char* cowPaths[] = {"/usr/local/opt/cowsay/share/cows", "/usr/share/cowsay/cows", "/opt/local/share/cowsay/cows"};
int cowPathsCount = 3;

vector<string> getFriends(DIR* cowdir) {
	vector<string> friends;
	struct dirent *entry;
	while((entry = readdir(cowdir)) != NULL) {
		friends.push_back(entry->d_name);
	}
	closedir (cowdir);
	return friends;
}

vectorstring> getCows() {
	DIR *cowdir;
	for(int i = 0; i < cowPathsCount; i++) {
		if((cowdir = opendir(cowPaths[i])) != NULL) {
			return getFriends(cowdir);
		}
	}
	cout << "Error: couldn't find a valid cowpath!" << endl;
	exit(1);
}


int main(int argc, char *argv[]) {
	auto friends = getCows();
	for(string i : friends) {
		cout << i << endl;
	}
}
