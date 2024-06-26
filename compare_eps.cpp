#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

/*
Let "sol_a" be the first solution file,
"sol_b" the second solution file,
and "gen" the generator file
(the binary file for c++, the source code with extension .py for python, and .class file for java)

The program repeatedly feed the output of "gen" to "sol_a" and "sol_b" until it encounters a case on which two solutions produce outputs which differ by more than "eps". The case is stored in the file "in".

[Instructions]
1. Compile "compare_eps.cpp" to create the binary file "compare_eps"
2. Put "sol_a", "sol_b", and "compare_eps" in the same directory
3. Create "stress" directory within the directory
4. Execute the following command: "compare_eps sol_a sol_b"
*/

void check_status(int status, const string &where){
	if(status < 0) cout << where << " -> error: " << strerror(errno) << "\n";
	else if(status >> 8) cout << where << " -> program exited abnormally\n";
	else return;
	exit(0);
}

string execution_command(string s){
	if(s.size() >= 4 && s.substr(s.size() - 3) == ".py") s = "python3 ./" + s;
	else if(s.size() >= 7 && s.substr(s.size() - 6) == ".class") s = "java ./" + s.substr(0, s.size() - 6);
	else if(s.size() >= 6 && s.substr(s.size() - 5) == ".sage") s = "sage ./" + s;
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
	static const double eps = 1e-5;
	char result_type;
	cin >> result_type;
	for(auto i = 0; ; ++ i){
		check_status(system("./gen> ./in"), "Generator");
		auto p1 = high_resolution_clock::now();
		check_status(system((sol_a_exe + " < ./in > ./stress/out_a").c_str()), sol_a);
		auto p2 = high_resolution_clock::now();
		check_status(system((sol_b_exe + " < ./in > ./stress/out_b").c_str()), sol_b);
		auto p3 = high_resolution_clock::now();
		ifstream in_a("./stress/out_a"), in_b("./stress/out_b");
		vector<double> a, b;
		for(double t; in_a >> t; a.push_back(t));
		for(double t; in_b >> t; b.push_back(t));
		cout << "Case #" << i << "\n";
		cout << sol_a << ": " << duration<double>(p2 - p1).count() << " seconds\n";
		cout << sol_b << ": " << duration<double>(p3 - p2).count() << " seconds" << endl;
		bool fail = false;
		if((int)a.size() != (int)b.size()) fail = true;
		else{
			for(auto i = 0; i < (int)a.size(); ++ i) if(abs(a[i] - b[i]) > eps){
				fail = true;
				break;
			}
		}
		if(fail){
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