#include "static_data.h"

HttpFieldData *HttpFieldData::m_pInstance = nullptr;

bool HttpFieldData::LoadData(const std::string &fname){
	if(!trie_->LoadFile(fname)){
		return false;
	}
	return true;
}
