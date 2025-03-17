#include <bits/stdc++.h>
using namespace std;



int main(int argc, char *argv[]){
	const string cpp_version = argv[1];
	const string stdcpp_location = "/usr/local/gcc-14/include/c++/14.2.0/x86_64-pc-linux-gnu/bits/stdc++.h";
	assert(11 <= stoi(cpp_version) && stoi(cpp_version) % 3 == 2);
	system(string("mkdir -p /home/aeren-wsl/Precompiled_Headers").c_str());
	system(string("mkdir -p /home/aeren-wsl/Precompiled_Headers/bits").c_str());
	system(("g++ -Winvalid-pch -std=c++" + cpp_version + " -DLOCAL -I/home/aeren-wsl/Precompiled_Headers -Wno-unused-result -fconcepts -g -fsanitize=address,undefined " + stdcpp_location + " -o /home/aeren-wsl/Precompiled_Headers/bits/stdc++.h.gch").c_str());
	return 0;
}

/*

*/

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                                   Coded by Aeren                                   //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////