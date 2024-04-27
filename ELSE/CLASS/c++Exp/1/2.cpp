#include <iostream> // 头文件
// using namespace std;
int main()
{
    int iv1, iv2; // 定义两个整型变量
    char cv1, cv2; // 定义两个字符型变量
    std::cout << "iv1 = " << iv1 << " iv2 = " << iv2 << std::endl; // 输出iv1和iv2的值
    std::cout << "size of iv1 = " << sizeof(iv1) << std::endl; // 输出iv1的字节长度
    std::cout << "size of cv1 = " << sizeof(cv1) << std::endl; // 输出cv1的字节长度
    // std::cout << sizeof(double) << std::endl; // 输出double类型的字节长度
    std::cout << "please enter two numbers: "; // 提示用户输入两个数
    std::cin >> iv1 >> iv2; // 输入两个整型数
    cv1 = ++iv1; // 将iv1加1后赋值给cv1
    cv2 = iv2++; // 将iv2赋值给cv2后再将iv2加1
    std::cout << "cv1 = " << cv1 << ", cv2 = " << cv2 << std::endl; // 输出cv1和cv2的值
    cv2 = 125; // 将cv2的值赋为125
    std::cout << cv2 << std::endl; // 输出cv2的值
    return 0;
}