/* 
 * This is for some io operations
 * or some helpers to load parameter
 * or some constants can store here
 */

#ifndef CORE_H
#define CORE_H

#include <vector>
#include <iostream>
std::string* ReadFile(const std::string& fileName){
    
}

// Erro and other info can be loaded here.
static void LOG_INFO(const std::string& msg){
    std::cerr<<"[INFO]"<<msg<<std::endl;
}

static void LOG_ERROR(const std::string& msg){
    std::cerr<<"[ERROR]"<<msg<<std::endl;
}



/* All types */
typedef struct {

}Node;

#endif