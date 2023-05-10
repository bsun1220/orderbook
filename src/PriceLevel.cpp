#include "PriceLevel.hpp"


void PriceLevel::addId(long amount, long id){
        orderids.push_back(id);
        volume += amount; 
}

void PriceLevel::adjustId(long adj, long id, bool put_back){
        int i = 0; 
        while (orderids[i] != id){
            i++; 
        }
        orderids.erase(orderids.begin() + i);
        if(put_back) orderids.push_back(id); 

        volume += adj;
}

std::vector<long> PriceLevel::getIds(){
        return orderids; 
 }