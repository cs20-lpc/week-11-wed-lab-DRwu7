#include <iostream>
#include <vector>
#include <iomanip>
#include "LinearProbing.hpp"
#include "QuadraticProbing.hpp"
#include "DoubleHashing.hpp"

using namespace std;

// Fixed key set for reproducibility
const vector<int> keys = {
    101, 205, 309, 412, 518, 623, 734, 845, 956, 110,
    221, 332, 443, 554, 665, 776, 887, 998, 109, 210,
    321, 432, 543, 654, 765, 876, 987, 98, 209, 320,
    431, 542, 653, 764, 875, 986, 97, 208, 319, 430,
    541, 652, 763, 874, 985, 96, 207, 318, 429, 540,
    651, 762, 873, 984, 95, 206, 317, 428, 539, 650,
    761, 872, 983, 94, 205, 316, 427, 538, 649, 760,
    871, 982, 93, 204, 315, 426, 537, 648, 759, 870,
    981, 92, 203, 314, 425, 536, 647, 758, 869, 980,
    91, 202, 313, 424, 535, 646, 757, 868, 979, 90
};

int main() {
    const int M = 101;
    const int skip = 3;
    const int N = keys.size();

    // Create tables
    LinearProbing<int> linear(M, skip);
    QuadraticProbing<int> quadratic(M);
    DoubleHashing<int> doubleHash(M);

    vector<HashTableClosed<int>*> tables = {&linear, &quadratic, &doubleHash};
    vector<string> names = {"Linear Probing (skip=3)", "Quadratic Probing", "Double Hashing"};

    for (size_t t = 0; t < tables.size(); t++) {
        cout << "\n--- " << names[t] << " ---\n";
        int totalInsertProbes = 0;

        for (int k : keys)
            totalInsertProbes += tables[t]->insert(k); // Students implement

        cout << "Average probes (insert): " << fixed << setprecision(2)
             << static_cast<double>(totalInsertProbes) / N << "\n";

        // Search first 10 keys (present) and 10 keys not in table
        int totalSearchProbes = 0;
        int foundCount = 0;
        for (int i = 0; i < 10; ++i) {
            int keyPresent = keys[i];
            int keyAbsent = 1000 + i;

            auto [found1, probes1] = tables[t]->search(keyPresent); // Students implement
            totalSearchProbes += probes1;
            if (found1) foundCount++;

            auto [found2, probes2] = tables[t]->search(keyAbsent);
            totalSearchProbes += probes2;
        }
        cout << "Search hits (first 10 present keys): " << foundCount << "/10\n";
        cout << "Average probes (search): " << fixed << setprecision(2)
             << static_cast<double>(totalSearchProbes) / 20 << "\n";
    }

    return 0;
}
