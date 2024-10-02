#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

const int seed = 0;
mt19937 generator(seed); // generator


int rand_int(int start, int end) {
    std::uniform_int_distribution<int> dist(start, end); // distribution
    return dist(generator);
}

double rand_double() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(generator);
}

int main() {
    for (int i = 0; i < 5; i++) {
        cout << fixed << setprecision(2) << rand_double() << "\n";
    }
    return 0;
}
