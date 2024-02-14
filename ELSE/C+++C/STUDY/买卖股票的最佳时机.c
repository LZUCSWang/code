    int maxProfit(int* prices, int pricesSize){
        int min_prices=-999999,max_profit=0;
        for(int i=0;i<prices;i++){
            if(prices[i]<min_prices){
                min_prices=prices[i];
            }
            if(prices[i]-min_prices>max_profit){
                max_profit=prices[i]-min_prices;
            }
        }
        return max_profit;
    }