/*
 * *@*	Description: 
 * *@*	Version: 
 * *@*	Author: yusheng Gao
 * *@*	Date: 2021-08-02 20:47:28
 * *@*	LastEditors: yusheng Gao
 * *@*	LastEditTime: 2021-08-02 21:15:34
 */

#include <thread>
#include <vector>

#include "Logging.h"

Logging::LogLevel g_logLevel = Logging::LogLevel::DEBUG;

int main(){
    
    std::vector<std::thread> threads;

    for(int i = 0; i<5; ++i){
        threads.push_back(std::thread(
            [](){

                for(int j = 0; j<100; ++j){
                    LOG_DEBUG << std::this_thread::get_id() << " write log DEBUG";
                    LOG_INFO << std::this_thread::get_id() << " write log INFO";
                    LOG_WARN <<  std::this_thread::get_id() << " write log WARN";
                    LOG_ERROR << std::this_thread::get_id() << " write log ERROR";
                }
            }
        ));
    }

    for(auto& td : threads) if(td.joinable()) td.join();



    return 0;
}