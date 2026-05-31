#include <iostream>
using namespace std;

class IntegralImage {
private:
    int image[4][4];
    int integral[4][4];
    int rows;
    int cols;

public:
    IntegralImage() {
        rows = 4;
        cols = 4;

        int temp[4][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}
        };

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                image[i][j] = temp[i][j];
                integral[i][j] = 0;
            }
        }
    }

    void calculateIntegralImage() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int up = 0;
                int left = 0;
                int upLeft = 0;

                if (i > 0)
                    up = integral[i - 1][j];

                if (j > 0)
                    left = integral[i][j - 1];

                if (i > 0 && j > 0)
                    upLeft = integral[i - 1][j - 1];

                integral[i][j] = image[i][j] + up + left - upLeft;
            }
        }
    }

    void printOriginalImage() {
        cout << "\nOriginal Image Matrix:" << endl;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << image[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void printIntegralImage() {
        cout << "\nIntegral Image Matrix:" << endl;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << integral[i][j] << "\t";
            }
            cout << endl;
        }
    }

    int getRegionSum(int r1, int c1, int r2, int c2) {
        int total = integral[r2][c2];

        int top = 0;
        int left = 0;
        int topLeft = 0;

        if (r1 > 0)
            top = integral[r1 - 1][c2];

        if (c1 > 0)
            left = integral[r2][c1 - 1];

        if (r1 > 0 && c1 > 0)
            topLeft = integral[r1 - 1][c1 - 1];

        return total - top - left + topLeft;
    }

    void printTimeComplexity() {
        cout << "\nTime Complexity:" << endl;
        cout << "Build Integral Image: O(rows * cols)" << endl;
        cout << "Region Sum Query: O(1)" << endl;
    }
};

int main() {
    IntegralImage obj;

    cout << "===== Integral Image Program =====" << endl;

    obj.calculateIntegralImage();

    obj.printOriginalImage();
    obj.printIntegralImage();

    cout << "\nRegion Sum Example:" << endl;
    cout << "Region from (1,1) to (2,2)" << endl;
    cout << "Sum = " << obj.getRegionSum(1, 1, 2, 2) << endl;

    obj.printTimeComplexity();

    return 0;
}
