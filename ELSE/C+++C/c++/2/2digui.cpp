#include <iostream>
using namespace std;

// �ݹ鷽ʽ�������
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
        cout << "������ n �� r ��ֵ���Կո�ָ������� 0 0 �������򣩣�";
        cin >> n >> r;
        if (n == 0 && r == 0) {
            break;
        }
        if (n < r || n < 0 || r < 0) {
            cout << "n �� r ��ֵ������Ҫ������������" << endl;
            continue;
        }
        int result = C(n, r);
        cout << "�� " << n << " ����ͬ������ȡ " << r << " ����������ѡ��ĸ����ǣ�" << result << endl;
    }
    return 0;
}
