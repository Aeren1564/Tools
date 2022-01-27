#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

void check_status(int status, const string &where){
	if(status < 0) cout << where << " -> error: " << strerror(errno) << "\n";
	else if(status >> 8) cout << where << " -> program exited abnormally\n";
	else return;
	exit(0);
}

int main(int argc, char *argv[]){
	cin.tie(0)->sync_with_stdio(0);
	string sol = argv[1];
	cout << "Print the results? Type (y) or (n): ";
	cout.flush();
	char X;
	cin >> X;
	for(auto i = 0; ; ++ i){
		check_status(system("./gen> ./in"), "Generator");
		auto p1 = high_resolution_clock::now();
		check_status(system(("./" + sol + "<./in>./stress/out_a").c_str()), sol);
		auto p2 = high_resolution_clock::now();
		ifstream in_a("./stress/out_a");
		vector<string> a;
		for(string t; in_a >> t; a.push_back(t));
		cout << "Case #" << i << "\n";
		cout << sol << ": " << duration<double>(p2 - p1).count() << " seconds" << endl;
		cout << "Ok\n";
		if(X == 'y'){
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