template<class L, class R> ostream &operator<<(ostream &out, const pair<L, R> &p);
template<class Tuple, size_t N> struct _tuple_printer;
template<class... Args> ostream &_print_tuple(ostream &out, const tuple<Args...> &t);
template<class ...Args> ostream &operator<<(ostream &out, const tuple<Args...> &t);
template<class T> ostream &operator<<(typename enable_if<!is_same<T, string>::value, ostream>::type &out, const T &arr);
ostream &operator<<(ostream &out, const _Bit_reference &bit);
template<size_t SZ> ostream &operator<<(ostream &out, const bitset<SZ> &b);
template<class T, class A, class C>
ostream &operator<<(ostream &out, priority_queue<T, A, C> pq);
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
template<class T> ostream &operator<<(typename enable_if<!is_same<T, string>::value, ostream>::type &out, const T &arr){
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
template<size_t SZ> ostream &operator<<(ostream &out, const bitset<SZ> &b){
	for(auto i = 0; i < SZ; ++ i) out << b[i];
	return out;
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