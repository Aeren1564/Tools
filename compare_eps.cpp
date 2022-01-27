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
	string sol_a = argv[1], sol_b = argv[2];
	cout << "Print the results? Type (y) or (n): ";
	cout.flush();
	static const double eps = 1e-5;
	char X;
	cin >> X;
	for(auto i = 0; ; ++ i){
		check_status(system("./gen> ./in"), "Generator");
		auto p1 = high_resolution_clock::now();
		check_status(system(("./" + sol_a + " < ./in > ./stress/out_a").c_str()), sol_a);
		auto p2 = high_resolution_clock::now();
		check_status(system(("./" + sol_b + " < ./in > ./stress/out_b").c_str()), sol_b);
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
		if(X == 'y'){
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