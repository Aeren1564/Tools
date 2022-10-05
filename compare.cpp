#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

/*
Let "sol_a" be the first solution file,
"sol_b" the second solution file,
and "gen" the generator file
(the binary file for c++ and the source code with extension .py for python)

The program repeatedly feed the output of "gen" to "sol_a" and "sol_b" until it encounters a case on which two solutions produce different outputs. The case is stored in the file "in".

[Instructions]
1. Compile "compare.cpp" to create the binary file "compare"
2. Put "sol_a", "sol_b", and "compare" in the same directory
3. Create "stress" directory within the directory
4. Execute the following command: "compare sol_a sol_b"
*/

void check_status(int status, const string &where){
	if(status < 0) cout << where << " -> error: " << strerror(errno) << "\n";
	else if(status >> 8) cout << where << " -> program exited abnormally\n";
	else return;
	exit(0);
}

string execution_command(string s){
	if((int)s.size() >= 4 && s.substr((int)s.size() - 3) == ".py") s = "python3 ./" + s;
	else s = "./" + s;
	return s;
}

int main(int argc, char *argv[]){
	cin.tie(0)->sync_with_stdio(0);
	string sol_a = argv[1];
	string sol_a_exe = execution_command(sol_a);
	string sol_b = argv[2];
	string sol_b_exe = execution_command(sol_b);
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
		ifstream in_a("./stress/out_a"), in_b("./stress/out_b");
		vector<string> a, b;
		for(string t; in_a >> t; a.push_back(t));
		for(string t; in_b >> t; b.push_back(t));
		cout << "Case #" << i << "\n";
		cout << sol_a << ": " << duration<double>(p2 - p1).count() << " seconds\n";
		cout << sol_b << ": " << duration<double>(p3 - p2).count() << " seconds" << endl;
		if(a != b){
			cout << "Failed\n";
			cout << sol_a << ": ";
			for(auto s: a) cout << s << " ";
			cout << "\n";
			cout << sol_b << ": ";
			for(auto s: b) cout << s << " ";
			cout << "\n";
			break;
		}
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