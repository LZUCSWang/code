#include "Robot.h"

int main(){

    Robot r1("R2");         // Create 3 robots
    Robot r2("D2");         // with different strategies    
    Robot r3("Z2");         // and execute commands

    r1.setStrategy(std::make_unique<AggressiveStrategy>()); // Set strategies
    r2.setStrategy(std::make_unique<NeutralStrategy>());    //传入的是unique_ptr，所以这里用make_unique，不用new
    r3.setStrategy(std::make_unique<DefensiveStrategy>());  //传入父类指针。

    std::cout<<"\n";    
    r1.executeCommand();    // 执行命令
    r2.executeCommand();
    r3.executeCommand();

    r1.setStrategy(std::make_unique<DefensiveStrategy>());  // Change strategies
    r2.setStrategy(std::make_unique<AggressiveStrategy>()); 

    std::cout<<"\n";
    r1.executeCommand();
    r2.executeCommand();
    r3.executeCommand();
}