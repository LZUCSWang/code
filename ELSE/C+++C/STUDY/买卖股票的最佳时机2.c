#include<stdio.h>
int maxProfit(int* prices, int pricesSize){//可以多次买进卖出，但是卖出前不能买进
    int i,min=0,max_profit=0;
    for(i=0;i<pricesSize-1;i++){
        max_profit+=(prices[i+1]-prices[i])?(prices[i+1]-prices[i]):0;
    }
    return max_profit;
}