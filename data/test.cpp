#include "Trie.h"


int t_main(){
	std::string path = "HttpField";
	trie_node trie;
	trie.LoadFile(path);
	
	trie.AddWord("newWord");
	trie.ShowAllWords("");
	std::string input;
	while(true){
		std::cin>>input;
		if(input=="0"){
			break;
		}
		if(trie.IsExist(input)){
			std::cout<<"exist"<<std::endl;
		}
		else{
			std::cout<<"not exist"<<std::endl;
		}
	}
	
	return 0;
}
