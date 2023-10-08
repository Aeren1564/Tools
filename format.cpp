#include <bits/stdc++.h>
using namespace std;

/*
[Instructions]
1. Compile "format.cpp" to create the binary file "format".
2. Run "./format TABWIDTH < SOURCECODE > DESTINATION".
*/

int main(int argc, char *argv[]){
	cin.tie(0)->sync_with_stdio(0);
	const int tab_width = stoi(string(argv[1]));
	assert(tab_width >= 1);
	auto generate_functor = [&](
		string from,
		string to,
		bool allow_alphabetic_prefix,
		bool allow_alphabetic_suffix
	){
		auto f = [from, to, allow_alphabetic_prefix, allow_alphabetic_suffix](string &s)->void{
			for(auto i = 0; i + (int)from.size() <= (int)s.size(); ++ i){
				if(
					s.substr(i, (int)from.size()) == from &&
					(
						i == 0 ||
						allow_alphabetic_prefix ||
						!isalpha(s[i - 1])
					) &&
					(
						i + (int)from.size() == (int)s.size() ||
						allow_alphabetic_suffix ||
						!isalpha(s[i + (int)from.size()])
					)
				){
					s = s.substr(0, i) + to + s.substr(i + (int)from.size());
				}
			}
		};
		return f;
	};
	auto remove_tailing_space = [&](string &s)->void{
		while(!s.empty() && s.back() == ' ') s.pop_back();
	};
	auto replace_tab_with_space = [&](string &s)->void{
		static const string obj(tab_width, ' ');
		int i = 0, tab_cnt = 0;
		for(; i + tab_width <= (int)s.size(); i += tab_width){
			if(s.substr(i, tab_width) != obj) break;
			++ tab_cnt;
		}
		s = string(tab_cnt, '\t') + s.substr(i);
	};
	auto insert_space_to_increment_and_decrement = [&](string &s)->void{
		for(auto i = 0; i + 3 <= (int)s.size(); ++ i){
			if(isalpha(s[i]) && s[i + 1] == s[i + 2] && (s[i + 1] == '+' || s[i + 1] == '-')) s.insert(s.begin() + i + 1, ' ');
			if(s[i] == s[i + 1] && (s[i] == '+' || s[i] == '-') && isalpha(s[i + 2])) s.insert(s.begin() + i + 2, ' ');
		}
	};
	auto remove_parenthese_brace_space = generate_functor(") {", "){", true, true);
	auto remove_for_space = generate_functor("for (", "for(", false, true);
	auto replace_forint_with_forauto = generate_functor("for(int ", "for(auto ", false, true);
	auto remove_if_space = generate_functor("if (", "if(", false, true);
	auto remove_while_space = generate_functor("while (", "while(", false, true);
	for(string s; getline(cin, s); ){
		remove_tailing_space(s);
		replace_tab_with_space(s);
		insert_space_to_increment_and_decrement(s);
		remove_parenthese_brace_space(s);
		remove_for_space(s);
		replace_forint_with_forauto(s);
		remove_if_space(s);
		remove_while_space(s);
		cout << s << "\n";
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