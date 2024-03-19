#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

/*

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
	for(auto i = 0; ; ++ i){
		check_status(system("./gen > ./in"), "Generator");
		auto p1 = high_resolution_clock::now();
		if(system(("socat SYSTEM:" + sol_exe + " SYSTEM:" + interactor_exe).c_str())){
			cout << "Interaction exited abnormally on the following input\n";
			ifstream in("./in");
			for(string s; getline(in, s); ){
				cout << s << "\n";
			}
			return 0;
		}
		auto p2 = high_resolution_clock::now();
		cout << "Case #" << i << "\n";
		cout << "Interaction duration: " << duration<double>(p2 - p1).count() << " seconds\n";
		cout << "Ok\n";
		cout.flush();
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