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
	string sol = argv[1], checker = argv[2];
	cout << "Print the results? Type (y) or (n): ";
	cout.flush();
	char X;
	cin >> X;
	for(auto i = 0; ; ++ i){
		check_status(system("./gen > ./in"), "Generator");
		auto p1 = high_resolution_clock::now();
		check_status(system(("./" + sol + " < ./in > ./stress/out_a").c_str()), sol);
		auto p2 = high_resolution_clock::now();
		check_status(system(("(cat ./in; printf \"\\n\"; cat ./stress/out_a) | ./" + checker + " > ./stress/res").c_str()), checker);
		ifstream in_res("./stress/res"), in_a("./stress/out_a");
		int res;
		in_res >> res;
		vector<string> a;
		for(string t; in_a >> t; a.push_back(t));
		cout << "Case #" << i << "\n";
		cout << sol << ": " << duration<double>(p2 - p1).count() << " seconds" << endl;
		if(!res){
			cout << "WRONG ANSWER\n";
			cout << sol << ": ";
			for(auto s: a) cout << s << " ";
			cout << "\n";
			break;
		}
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