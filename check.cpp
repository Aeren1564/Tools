#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

/*
Let "sol" be the solution file,
"checker" the checker file,
and "gen" the generator file.
(the binary file for c++, the source code with extension .py for python, and .class file for java)

Checker should accept the input and the output of the solution file sequentially and exit abnormally (with assert, for example) iff it the output is wrong.

The program repeatedly feed the output of "gen" to "sol" until it encounters a case on which the solution produces a wrong output. The case is stored in the file "in".

[Instructions]
1. Compile "check.cpp" to create the binary file "check".
2. Put "sol", "checker", and "check" in the same directory.
3. Create "stress" directory within the directory.
4. Execute the following command: "check sol checker".
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
	string checker = argv[2];
	string checker_exe = execution_command(checker);
	cout << "Print the results? Type (y) or (n): ";
	cout.flush();
	char result_type;
	cin >> result_type;
	for(auto i = 0; ; ++ i){
		check_status(system("./gen > ./in"), "Generator");
		auto p1 = high_resolution_clock::now();
		check_status(system((sol_exe + " < ./in > ./stress/out_a").c_str()), sol);
		auto p2 = high_resolution_clock::now();
		check_status(system(("(cat ./in; printf \"\\n\"; cat ./stress/out_a) | " + checker_exe).c_str()), checker);
		ifstream in("./stress/out_a");
		vector<string> a;
		for(string t; in >> t; a.push_back(t));
		cout << "Case #" << i << "\n";
		cout << sol << ": " << duration<double>(p2 - p1).count() << " seconds" << endl;
		cout << "Ok\n";
		if(result_type == 'y'){
			cout << sol << ": ";
			for(auto s: a) cout << s << " ";
			cout << "\n";
		}
		cout << endl;
	}
	return 0;
}

/*

*/

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                                   Coded by Aeren                                   //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////