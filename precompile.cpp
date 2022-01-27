#include <bits/stdc++.h>
using namespace std;



int main(int argc, char *argv[]){
	string version = argv[1];
	assert(version == "11" || version == "14" || version == "17" || version == "20");
	system(string("mkdir -p /home/aeren/Precompiled_Headers/bits").c_str());
	system(("g++-11 -std=c++" + version + " -DLOCAL -I/home/aeren/Precompiled_Headers -Wno-narrowing -Winvalid-pch -Wno-unused-result -fconcepts -g -fsanitize=address,undefined /usr/include/x86_64-linux-gnu/c++/11/bits/stdc++.h -o /home/aeren/Precompiled_Headers/bits/stdc++.h.gch").c_str());
	system(string("mkdir -p /home/aeren/Precompiled_Headers/ext/pb_ds").c_str());
	system(("g++-11 -std=c++" + version + " -Winvalid-pch -Wno-narrowing -DLOCAL -fconcepts -g -fsanitize=address,undefined /usr/include/c++/11/ext/pb_ds/assoc_container.hpp -o /home/aeren/Precompiled_Headers/ext/pb_ds/assoc_container.hpp.gch").c_str());
	system(("g++-11 -std=c++" + version + " -Winvalid-pch -Wno-narrowing -DLOCAL -fconcepts -g -fsanitize=address,undefined /usr/include/c++/11/ext/pb_ds/tree_policy.hpp -o /home/aeren/Precompiled_Headers/ext/pb_ds/tree_policy.hpp.gch").c_str());
	return 0;
}

/*

*/

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                                   Coded by Aeren                                   //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////