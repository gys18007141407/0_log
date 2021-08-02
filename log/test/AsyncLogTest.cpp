/*
 * *@*	Description: 
 * *@*	Version: 
 * *@*	Author: yusheng Gao
 * *@*	Date: 2021-08-02 20:47:28
 * *@*	LastEditors: yusheng Gao
 * *@*	LastEditTime: 2021-08-02 21:15:31
 */

#include <mutex>
#include <thread>
#include <vector>
#include <unistd.h>

#include "Logging.h"
#include "AsynLog.h"

Logging::LogLevel g_logLevel = Logging::LogLevel::DEBUG;

std::unique_ptr<AsynLog> g_AsynLogfile;

void outputFUNC(const char* log, std::size_t len){
    g_AsynLogfile->append(log, len);
}

int main(){

    Logging::setOutFunc(outputFUNC);
    g_AsynLogfile.reset(new AsynLog(__FILE__, 1024*1024));

    g_AsynLogfile->start();

    std::vector<std::thread> threads;
    for(int i = 0; i<4; ++i){
        threads.push_back(std::thread(
 
            []()->void{
                for(int j = 0; j<10000; ++j){
                    LOG_INFO << std::this_thread::get_id() << " write log INFO";
                    LOG_WARN << std::this_thread::get_id() << " write log WARN";
                }
            }
        ));
    }

    for(auto& td : threads) if(td.joinable()) td.join();

    return 0;
}