#include <bits/stdc++.h>
using namespace std;



int main(int argc, char *argv[]){
	const string cpp_version = argv[1];
	const string gcc_version = "13";
	assert(11 <= stoi(cpp_version) && stoi(cpp_version) % 3 == 2 && stoi(cpp_version) <= 23);
	system(string("mkdir -p /home/aeren/Precompiled_Headers/bits").c_str());
	system(("g++-" + gcc_version + " -Winvalid-pch -std=c++" + cpp_version + " -DLOCAL -I/home/aeren/Precompiled_Headers -Wno-narrowing -Wno-unused-result -fconcepts -g -fsanitize=address,undefined /usr/include/x86_64-linux-gnu/c++/" + gcc_version + "/bits/stdc++.h -o /home/aeren/Precompiled_Headers/bits/stdc++.h.gch").c_str());
	return 0;
}

/*

*/

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                                   Coded by Aeren                                   //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////