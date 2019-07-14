#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

//先简单实现一个char的，然后再实现中文的场景，使用模板或者string。需要使用切字代码。
class trie_node{
	private:
		int status;
		std::unordered_map<char,trie_node *> children;
	public:
		trie_node(){
			status = 0;
		}
		// @brief:set status 1
		void SetStatus(){ this->status = 1; }

		// @brief:get status value
		int GetStatus(){ return status; }

		// @brief:add word to trie
		bool AddWord(const std::string &word);

		// @brief:add per line in file to trie
		bool LoadFile(const std::string &path);

		// @brief:judge word in trie
		bool IsExist(const std::string &word);

		// @brief:print all exist word to stdout
		void ShowAllWords(std::string word);

		// @brief:get a exist word from char vector
		bool ParseWordFromVector(std::vector<char>::iterator &locate,std::vector<char>::iterator end){
			auto trie = this;
			for(locate;locate!=end;locate++){
				if(trie->children.find(*locate)==trie->children.end()){
					return false;
				}
				trie=trie->children[*locate];
				if(trie->status == 1){
					return true;
				}
			}
			return false;
		}

		// @brief:get an exist word form a string
		bool ParseWordFormString(std::string::iterator &locate,std::string::iterator end){
			auto trie = this;
			for(locate;locate!=end;locate++){
				if(trie->children.find(*locate)==trie->children.end()){
					return false;
				}
				trie=trie->children[*locate];
				if(trie->status == 1){
					return true;
				}
			}
			return false;
		}
};

#endif
