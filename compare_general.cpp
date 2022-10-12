#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

/*
Let "sol_a" be the first solution file,
"sol_b" the second solution file,
"checker" the checker file,
and "gen" the generator file.
(the binary file for c++, the source code with extension .py for python, and .class file for java)

Checker should accept the input, the output of the first solution file, and the output of the second solution file sequentially and exit abnormally (with assert, for example) iff the output is wrong.

The program repeatedly feed the output of "gen" to "sol_a" and "sol_b" until it encounters a case on which the solutions produce wrong outputs. The case is stored in the file "in".

[Instructions]
1. Compile "compare_general.cpp" to create the binary file "compare_general".
2. Put "sol_a", "sol_b", "checker", and "compare_general" in the same directory.
3. Create "stress" directory within the directory.
4. Execute the following command: "compare_general sol_a sol_b checker".
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
	string sol_a = argv[1];
	string sol_a_exe = execution_command(sol_a);
	string sol_b = argv[2];
	string sol_b_exe = execution_command(sol_b);
	string checker = argv[3];
	string checker_exe = execution_command(checker);
	cout << "Print the results? Type (y) or (n): ";
	cout.flush();
	char result_type;
	cin >> result_type;
	for(auto i = 0; ; ++ i){
		check_status(system("./gen > ./in"), "Generator");
		auto p1 = high_resolution_clock::now();
		check_status(system((sol_a_exe + " < ./in > ./stress/out_a").c_str()), sol_a);
		auto p2 = high_resolution_clock::now();
		check_status(system((sol_b_exe + " < ./in > ./stress/out_b").c_str()), sol_b);
		auto p3 = high_resolution_clock::now();
		check_status(system(("(cat ./in; printf \"\\n\"; cat ./stress/out_a; printf \"\\n\"; cat ./stress/out_b;) | " + checker_exe).c_str()), checker);
		ifstream in_a("./stress/out_a"), in_b("./stress/out_b");
		vector<string> a, b;
		for(string t; in_a >> t; a.push_back(t));
		for(string t; in_b >> t; b.push_back(t));
		cout << "Case #" << i << "\n";
		cout << sol_a << ": " << duration<double>(p2 - p1).count() << " seconds\n";
		cout << sol_b << ": " << duration<double>(p3 - p2).count() << " seconds" << endl;
		cout << "Ok\n";
		if(result_type == 'y'){
			cout << sol_a << ": ";
			for(auto s: a) cout << s << " ";
			cout << "\n";
			cout << sol_b << ": ";
			for(auto s: b) cout << s << " ";
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