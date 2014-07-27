#include <iostream>
#include <cmath>

using namespace std;

bool is_prime(int n)
{
    if (n % 2 == 0) {
        return false;
    } else {
        for (int y = 3; y <= ceil(sqrt(n)); y += 2) {
            if (n % y == 0) {
                return false;
            }
        }
        return true;
    }
}

int main()
{
    for (int found = 0, candidate = 3; found < 100; candidate++) {
        if (is_prime(candidate)) {
            cout << candidate << " ";
            found++;
        }
    }
    cout << flush << endl;
}
