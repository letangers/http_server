#ifndef STATIC_DATA_H
#define STATIC_DATA_H

#include "Trie.h"

class StaticData{
	public:
		StaticData(){
			trie_ = new trie_node();
		}
		virtual ~StaticData(){}

		virtual bool LoadFile(const std::string &fname) = 0;
		trie_node * trie_;
};

class HttpFieldData : public StaticData{
	public:
		static HttpFieldData *m_pInstance;
		static HttpFieldData *GetInstance(){
			if (m_pInstance == nullptr){
				m_pInstance = new HttpFieldData();
			}
			return m_pInstance;
		}
	virtual bool LoadFile(const std::string &fname);
};

#endif
