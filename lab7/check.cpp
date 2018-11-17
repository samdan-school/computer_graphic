#include <iostream>
#include <vector>
using namespace std;

void changeVector(vector<int> &a) {
    a[0] = 9;
}

int main(int argc, char const *argv[]) {
    vector<int> a = {1, 2, 3};

    changeVector(a);

    cout << a[0] << " " << a[1] << " " << a[2] << endl;

    return 0;
}
