#include "monitor.hpp"
#include <thread>
#include <vector>
#include <iostream>

Monitor<std::vector<int>> sync_vector {1};
std::vector<std::thread> threads;

int main() {
    for(int i=0;i<4;i++) {
        threads.push_back(std::thread([&](){
            for(int j=0;j<10;j++) {
                sync_vector->push_back(j);
            }
        }));
    }

    for(auto& t : threads) {
        t.join();
    }

    {
        auto handler = sync_vector.get_access();
        handler->push_back(11);
    }
    
    auto& v = sync_vector.unsafe_get_access();

    v.push_back(111);

    for(auto &it: v) {
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;

    return 0;
}