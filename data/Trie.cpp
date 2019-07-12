#include "Trie.h"

bool trie_node::AddWord(const std::string &word){
	trie_node * trie = this;
	for(int i = 0;i<word.length();i++){
		if(trie->children.find(word[i])==trie->children.end()){
			trie->children[word[i]] = new trie_node();
		}
		trie = trie->children[word[i]];
	}
	trie->SetStatus();
	return true;
}

bool trie_node::LoadFile(const std::string &path){
	if(path.empty()){
		std::cout<<"path is empty"<<std::endl;
		return false;
	}
	std::ifstream fin(path);
	if(!fin.is_open()){
		std::cout<<"open file "<<path<<" failed"<<std::endl;
		return false;
	}
	std::string line;
	while(std::getline(fin,line)){
		line.erase(line.find_last_not_of(" \t\r\n")+1);
		this->AddWord(line);
	}
	fin.close();
	return true;
}

bool trie_node::IsExist(const std::string &word){
	trie_node * trie = this;
	for(int i = 0;i<word.length();i++){
		if(trie->children.find(word[i])==trie->children.end()){
			return false;
		}
		trie = trie->children[word[i]];
	}
	if(trie->GetStatus() == 0){
		return false;
	}
	return true;
}

void trie_node::ShowAllWords(std::string word){
	if(this->GetStatus() == 1){
		std::cout<<word<<std::endl;
	}
	for(auto one : children){
		one.second->ShowAllWords(word + one.first);
	}
}
