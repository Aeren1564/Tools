#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

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
	string sol = argv[1];
	string sol_exe = execution_command(sol);
	cout << "Print the results? Type (y) or (n): ";
	cout.flush();
	char result_type;
	cin >> result_type;
	for(auto i = 0; ; ++ i){
		check_status(system("./gen> ./in"), "Generator");
		auto p1 = high_resolution_clock::now();
		check_status(system((sol_exe + " < ./in > ./stress/out_a").c_str()), sol);
		auto p2 = high_resolution_clock::now();
		ifstream in_a("./stress/out_a");
		vector<string> a;
		for(string t; in_a >> t; a.push_back(t));
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