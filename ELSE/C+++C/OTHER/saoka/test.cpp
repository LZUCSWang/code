#include <iostream>
using namespace std;

class Rect {
private:
    float* Length;
    float* Width;
public:
    // Constructor with default values
    Rect(float len = 1, float wid = 1) {
        Length = new float(len);
        Width = new float(wid);
    }

    // Destructor to free dynamically allocated memory
    ~Rect() {
        delete Length;
        delete Width;
    }

    // Function to set Length and Width
    void set(float len = 0, float wid = 0) {
        *Length = len;
        *Width = wid;
    }

    // Function to calculate and return perimeter
    float perimeter() {
        return 2 * (*Length + *Width);
    }

    // Function to calculate and return area
    float area() {
        return (*Length) * (*Width);
    }
};

int main() {
    // Method 1
    Rect r1;
    r1.set(20, 30);

    // Method 2
    Rect* p = new Rect(r1);
    p->set(20, 13);

    // Print results
    cout << "Perimeter of r1: " << r1.perimeter() << endl;
    cout << "Area of r1: " << r1.area() << endl;
    cout << "Perimeter of p: " << p->perimeter() << endl;
    cout << "Area of p: " << p->area() << endl;

    // Free dynamically allocated memory
    delete p;

    return 0;
}
