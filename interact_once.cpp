#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

/*
Let "a" be the first solution file,
and "interactor" the second solution file.
(the binary file for c++, the source code with extension .py for python, and .class file for java)

The program feed the input in "in" to "interactor", then simultaneously run "a" and "interactor" by interlocking their stdin and stdout, and check if "interactor" exits successfully.

[Instructions]
1. Compile "interact_once.cpp" to create the binary file "interact_once"
2. Put "in", "a", and "interact_once" in the same directory
3. Execute the following command: "./interact_once a interactor"
*/

void check_status(int status, const string &where){
	if(status < 0) cout << where << " -> error: " << strerror(errno) << "\n";
	else if(status >> 8) cout << where << " -> program exited abnormally\n";
	else return;
	exit(0);
}

string execution_command(string s){
	if(s.size() >= 4 && s.substr(s.size() - 3) == ".py") s = "python3 ./" + s;
	else if(s.size() >= 7 && s.substr(s.size() - 6) == ".class") s = "java " + s.substr(0, s.size() - 6);
	else s = "./" + s;
	return s;
}

int main(int argc, char *argv[]){
	cin.tie(0)->sync_with_stdio(0);
	string sol = argv[1];
	string sol_exe = execution_command(sol);
	string interactor = argv[2];
	string interactor_exe = execution_command(interactor);
	system("rm /tmp/fifo");
	system("mkfifo /tmp/fifo");
	auto p1 = high_resolution_clock::now();
	check_status(system(("(cat ./in ; " + sol_exe + " < /tmp/fifo) | " + interactor_exe + " > /tmp/fifo").c_str()), "Interaction");
	auto p2 = high_resolution_clock::now();
	cout << "Interaction duration: " << duration<double>(p2 - p1).count() << " seconds\n";
	cout << "Ok\n";
	cout.flush();
	return 0;
}

/*

*/

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                                   Coded by Aeren                                   //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////