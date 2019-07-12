#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include "Io.h"

class Buffer{
	private:
		std::vector<char> buffer_;
		int head_;
		int tail_;

	public:
		Buffer():head_(-1),tail_(0){}
		~Buffer(){}
		void Clear(){
			head_ = -1;
			tail_ = 0;
			buffer_.clear();
			buffer_.shrink_to_fit();
		}

		int RecvBuf(int fd, int length);
		int SendBuf(int fd, int length);
};

#endif
