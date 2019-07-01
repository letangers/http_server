/* 
 * @author:letangers
 * @email :letangers@gmail.com
 * @brief :define some function to deal err
 *         定义一些错误处理函数
 */
#ifndef ERR_H
#define ERR_H

#include <iostream>
#include <string>


void err(const std::string & err_info){
	std::cerr<<err_info<<std::endl;
}

#endif
