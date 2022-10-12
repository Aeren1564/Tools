#include <bits/stdc++.h>
using namespace std;

string execution_command(string s){
	if(s.size() >= 4 && s.substr(s.size() - 3) == ".py") s = "python3 ./" + s;
	else if(s.size() >= 7 && s.substr(s.size() - 6) == ".class") s = "java " + s.substr(0, s.size() - 6);
	else s = "./" + s;
	return s;
}

int main(int argc, char *argv[]){
	string s = argv[1];
	string s_exe = execution_command(s);
	system(("/usr/bin/time -f \"Time: %E (M:S)\nMemory: %M (KB)\" " + s_exe + "<in").c_str());
	return 0;
}

/*

*/

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                                   Coded by Aeren                                   //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////