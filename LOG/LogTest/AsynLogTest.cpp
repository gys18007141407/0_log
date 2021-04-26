#include "logBase/AsynLog.h"
#include "logBase/Logging.h"
#include <mutex>
#include <thread>
#include <vector>
#include <unistd.h>

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