#include <iostream>
#include <string>
using namespace std;

class HammingDistance {
private:
    string str1;
    string str2;

public:
    HammingDistance(string s1, string s2) {
        str1 = s1;
        str2 = s2;
    }

    int calculateDistance() {

        if (str1.length() != str2.length()) {
            cout << "Error: Strings must have the same length." << endl;
            return -1;
        }

        int distance = 0;

        cout << "\nComparison Process:" << endl;

        for (int i = 0; i < str1.length(); i++) {

            cout << "Position " << i + 1 << ": ";

            cout << str1[i] << " vs " << str2[i];

            if (str1[i] != str2[i]) {
                distance++;
                cout << " -> Different";
            }
            else {
                cout << " -> Same";
            }

            cout << endl;
        }

        return distance;
    }

    void printTimeComplexity() {
        cout << "\nTime Complexity:" << endl;
        cout << "Hamming Distance: O(n)" << endl;
    }
};

int main() {

    string s1, s2;

    cout << "===== Hamming Distance Program =====" << endl;

    cout << "Enter first string: ";
    cin >> s1;

    cout << "Enter second string: ";
    cin >> s2;

    HammingDistance hd(s1, s2);

    int result = hd.calculateDistance();

    if (result != -1) {
        cout << "\nHamming Distance = " << result << endl;
    }

    hd.printTimeComplexity();

    return 0;
}
