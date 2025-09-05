/// Status: not tested

#pragma once

template <typename T>
struct Matrix {
    int n;
    vector<vector<T>> a;

    Matrix(int n_) : n(n_), a(n, vector<T>(n)) {}

    Matrix operator+(const Matrix& rhs) const {
        assert(n == rhs.n);
        Matrix res(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res.a[i][j] = a[i][j] + rhs.a[i][j];
            }
        }
    }

    Matrix operator-(const Matrix& rhs) const {
        assert(n == rhs.n);
        Matrix res(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res.a[i][j] = a[i][j] - rhs.a[i][j];
            }
        }
    }

    Matrix operator*(const Matrix& rhs) const {
        assert(n == rhs.n);
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res.a[i][j] = 0;

                for (int k = 0; k < n; k++) {
                    res.a[i][j] += a[i][j] * rhs.a[i][j];
                }
            }
        }
    }

    double determinant(vector<vector<double>>& a, int n) {
        const double EPS = 1e-9;
        double det = 1;

        for (int i = 0; i < n; i++) {
            int k = i;

            for (int j = i + 1; j < n; j++) {
                if (abs(a[j][i]) > abs(a[k][i])) {
                    k = j;
                }
            }

            if (abs(a[k][i]) < EPS) {
                det = 0;
                break;
            }

            swap(a[i], a[k]);
            if (i != k) det = -det;
            det *= a[i][i];

            for (int j = i + 1; j < n; j++) {
                a[i][j] /= a[i][i];
            }

            for (int j = 0; j < n; j++) {
                if (j != i && abs(a[j][i]) > EPS) {
                    for (int k = i + 1; k < n; k++) {
                        a[j][k] -= a[i][k] * a[j][i];
                    }
                }
            }
        }

        return det;
    }
};
