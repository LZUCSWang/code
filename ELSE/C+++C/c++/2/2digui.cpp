#include <iostream>
using namespace std;

// 递归方式求组合数
int C(int n, int r) {
    if (n < r || n < 0 || r < 0) {
        return 0;
    } else if (n == r || r == 0) {
        return 1;
    } else {
        return C(n-1, r-1) + C(n-1, r);
    }
}

int main() {
    int n, r;
    while (true) {
        cout << "请输入 n 和 r 的值（以空格分隔，输入 0 0 结束程序）：";
        cin >> n >> r;
        if (n == 0 && r == 0) {
            break;
        }
        if (n < r || n < 0 || r < 0) {
            cout << "n 和 r 的值不符合要求，请重新输入" << endl;
            continue;
        }
        int result = C(n, r);
        cout << "从 " << n << " 个不同的数中取 " << r << " 个数的所有选择的个数是：" << result << endl;
    }
    return 0;
}
