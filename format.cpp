#include <bits/stdc++.h>
using namespace std;

/*
[Instructions]
1. Compile "format.cpp" to create the binary file "format".
2. Run "./format TABWIDTH < SOURCECODE > DESTINATION".
*/

// DEBUG BEGIN
#ifdef LOCAL
// DECLARATION BEGIN
template<class L, class R> ostream &operator<<(ostream &out, const pair<L, R> &p);
template<class Tuple, size_t N> struct _tuple_printer;
template<class... Args> ostream &_print_tuple(ostream &out, const tuple<Args...> &t);
template<class ...Args> ostream &operator<<(ostream &out, const tuple<Args...> &t);
template<class T> ostream &operator<<(class enable_if<!is_same<T, string>::value, ostream>::type &out, const T &arr);
ostream &operator<<(ostream &out, const _Bit_reference &bit);
template<class T, class A, class C>
ostream &operator<<(ostream &out, priority_queue<T, A, C> pq);
// DECLARATION END
template<class L, class R> ostream &operator<<(ostream &out, const pair<L, R> &p){
	return out << "{" << p.first << ", " << p.second << "}";
}
template<class Tuple, size_t N> struct _tuple_printer{
	static ostream &_print(ostream &out, const Tuple &t){ return _tuple_printer<Tuple, N-1>::_print(out, t) << ", " << get<N-1>(t); }
};
template<class Tuple> struct _tuple_printer<Tuple, 1>{
	static ostream &_print(ostream &out, const Tuple& t){ return out << get<0>(t); }
};
template<class... Args> ostream &_print_tuple(ostream &out, const tuple<Args...> &t){
	return _tuple_printer<decltype(t), sizeof...(Args)>::_print(out << "{", t) << "}";
}
template<class ...Args> ostream &operator<<(ostream &out, const tuple<Args...> &t){
	return _print_tuple(out, t);
}
template<class T> ostream &operator<<(class enable_if<!is_same<T, string>::value, ostream>::type &out, const T &arr){
	if(arr.empty()) return out << "{}";
	out << "{";
	for(auto it = arr.begin(); it != arr.end(); ++ it){
		out << *it;
		next(it) != arr.end() ? out << ", " : out << "}";
	}
	return out;
}
ostream &operator<<(ostream &out, const _Bit_reference &bit){
	return out << bool(bit);
}
template<class T, class A, class C>
ostream &operator<<(ostream &out, priority_queue<T, A, C> pq){
	vector<T> a;
	while(!pq.empty()) a.push_back(pq.top()), pq.pop();
	return out << a;
}
template<class Head>
void debug_out(Head H){ cerr << H << endl; }
template<class Head, class... Tail>
void debug_out(Head H, Tail... T){ cerr << H << ", ", debug_out(T...); }
void debug2_out(){ }
template<class Head, class... Tail>
void debug2_out(Head H, Tail... T){ cerr << "\n"; for(auto x: H) cerr << x << ",\n"; debug2_out(T...); }
template<class Width, class Head>
void debugbin_out(Width w, Head H){
	for(auto rep = w; rep; -- rep, H >>= 1) cerr << (H & 1);
	cerr << endl;
}
template<class Width, class Head, class... Tail>
void debugbin_out(Width w, Head H, Tail... T){
	for(auto rep = w; rep; -- rep, H >>= 1) cerr << (H & 1);
	cerr << ", "; debugbin_out(w, T...);
}
enum CODE{ CCRED = 31, CCGREEN = 32, CCYELLOW = 33, CCBLUE = 34, CCDEFAULT = 39 };
#define debug_endl() cerr << endl
#define debug(...) cerr << "\033[" << (int)CODE(CCRED) << "mL" << setw(3) << std::left << __LINE__ << std::right << " [" << #__VA_ARGS__ << "] \033[" << (int)CODE(CCBLUE) << "m", debug_out(__VA_ARGS__), cerr << "\33[" << (int)CODE(CCDEFAULT) << "m"
#define debug2(...) cerr << "\033[" << (int)CODE(CCRED) << "mL" << setw(3) << std::left << __LINE__ << std::right << " [" << #__VA_ARGS__ << "] \033[" << (int)CODE(CCBLUE) << "m", debug2_out(__VA_ARGS__), cerr << "\33[" << (int)CODE(CCDEFAULT) << "m"
#define debugbin(...) cerr << "\033[" << (int)CODE(CCRED) << "mL" << setw(3) << std::left << __LINE__ << std::right << " [" << #__VA_ARGS__ << "] \033[" << (int)CODE(CCBLUE) << "m", debugbin_out(__VA_ARGS__), cerr << "\33[" << (int)CODE(CCDEFAULT) << "m"
#else
#define debug_endl() 42
#define debug(...) 42
#define debug2(...) 42
#define debugbin(...) 42
#endif
// DEBUG END

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