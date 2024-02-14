#include<stdio.h>
int maxprofit(int *prices,int pricesSize){
    int max_profit=0,min_prices=99999999;
    for(int i=0;i<pricesSize;i++){
        if(prices[i]<min_prices)min_prices=prices[i];
        else if(prices[i]-min_prices>max_profit)max_profit=prices[i]-min_prices;
    }
    return max_profit;
}
int main(){
    int pri[]={7,1,5,3,6,4};
    printf("%d",maxprofit(pri,6));
}