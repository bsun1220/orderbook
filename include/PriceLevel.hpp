#include <vector>

class PriceLevel {
    public:
        double price {};
        long volume{};
        std::vector <long> orderids{};
    
    PriceLevel(double act_price){
        volume = 0; 
        price = act_price; 
    }

    void addId(long amount, long id);
    void adjustId(long adj, long id, bool put_back);
    std::vector<long> getIds();

};