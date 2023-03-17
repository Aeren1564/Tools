#include <bits/stdc++.h>
using namespace std;

/*
[Instructions]
1. Compile "replace_space_with_tab.cpp" to create the binary file "replace_space_with_tab"
2. It will read a space-formatted code and output a tab-formatted code.
*/

int main(int argc, char *argv[]){
	cin.tie(0)->sync_with_stdio(0);
	int tab_width = stoi(string(argv[1]));
	for(string s; getline(cin, s); ){
		int i = 0;
		while(i + tab_width <= (int)s.size()){
			for(auto j = 0; j < tab_width; ++ j) if(s[i + j] != ' ') goto DONE;
			cout << '\t';
			i += tab_width;
		}
		DONE:;
		cout << s.substr(i) << "\n";
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