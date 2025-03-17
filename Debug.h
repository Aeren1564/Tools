template<typename T>
using _is_container = std::integral_constant<bool, !std::is_same<T, std::string>::value && std::is_constructible<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>::value>;

ostream &operator<<(ostream &out, __uint128_t x){
	if(!x) return out << 0;
	constexpr int block = 1e9;
	array<int, 6> a{};
	int it = 0;
	for(; x; x /= block) a[it ++] = x % block;
	for(out << a[-- it]; -- it >= 0; ) out << setw(9) << setfill('0') << a[it];
	return out;
}
ostream &operator<<(ostream &out, __int128_t x){
	if(!x) return out << 0;
	if(x < 0) out << "-", x = -x;
	constexpr int block = 1e9;
	array<int, 6> a{};
	int it = 0;
	for(; x; x /= block) a[it ++] = x % block;
	for(out << a[-- it]; -- it >= 0; ) out << setw(9) << setfill('0') << a[it];
	return out;
}
template<size_t SZ> ostream &operator<<(ostream &out, typename bitset<SZ>::reference bit);
template<class L, class R> ostream &operator<<(ostream &out, const pair<L, R> &p);
template<class Tuple, size_t N> struct _tuple_printer;
template<class... Args> ostream &_print_tuple(ostream &out, const tuple<Args...> &t);
template<class ...Args> ostream &operator<<(ostream &out, const tuple<Args...> &t);
template<class T> ostream &operator<<(typename enable_if<_is_container<T>::value, ostream>::type &out, T &&arr);
template<class T, class A, class C>
ostream &operator<<(ostream &out, priority_queue<T, A, C> pq);
template<size_t SZ> ostream &operator<<(ostream &out, typename bitset<SZ>::reference bit){ return out << bool(bit); }
template<class L, class R> ostream &operator<<(ostream &out, const pair<L, R> &p){ return out << "{" << p.first << ", " << p.second << "}"; }
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
template<class T> ostream &operator<<(typename enable_if<_is_container<T>::value, ostream>::type &out, T &&arr){
	if(arr.empty()) return out << "{}";
	out << "{";
	for(auto it = arr.begin(); it != arr.end(); ++ it){
		out << *it;
		next(it) != arr.end() ? out << ", " : out << "}";
	}
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
void debug_bin_out(Width w, Head H){
	for(auto rep = w; rep; -- rep, H >>= 1) cerr << (H & 1);
	cerr << endl;
}
template<class Width, class Head, class... Tail>
void debug_bin_out(Width w, Head H, Tail... T){
	for(auto rep = w; rep; -- rep, H >>= 1) cerr << (H & 1);
	cerr << ", "; debug_bin_out(w, T...);
}
enum CODE{ CCRED = 31, CCGREEN = 32, CCYELLOW = 33, CCBLUE = 34, CCDEFAULT = 39 };
#define debug_endl() cerr << endl
#define debug(...) cerr << "\033[" << (int)CODE(CCRED) << "mL" << setw(3) << std::left << __LINE__ << std::right << " [" << #__VA_ARGS__ << "] \033[" << (int)CODE(CCBLUE) << "m", debug_out(__VA_ARGS__), cerr << "\33[" << (int)CODE(CCDEFAULT) << "m"
#define debug2(...) cerr << "\033[" << (int)CODE(CCRED) << "mL" << setw(3) << std::left << __LINE__ << std::right << " [" << #__VA_ARGS__ << "] \033[" << (int)CODE(CCBLUE) << "m", debug2_out(__VA_ARGS__), cerr << "\33[" << (int)CODE(CCDEFAULT) << "m"
#define debug_bin(first, ...) cerr << "\033[" << (int)CODE(CCRED) << "mL" << setw(3) << std::left << __LINE__ << std::right << " [BIN:" << #__VA_ARGS__ << "] \033[" << (int)CODE(CCBLUE) << "m", debug_bin_out(first, __VA_ARGS__)