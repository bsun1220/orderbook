
class Order{
    public:
        long uid {0};
        double price {0};
        bool side{true};
        long volume{0}; 
    
    Order(){}
    
    Order(long act_uid, double act_price, bool act_side, long act_volume){
        uid = act_uid;
        price = act_price;
        side = act_side;
        volume = act_volume;
    }

    void update_quantity(long act_volume);
    
};