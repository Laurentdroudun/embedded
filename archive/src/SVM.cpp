#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <iostream>
#include <Eigen/Core>
#include <Eigen/QR>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    // Charger les données d'entraînement
    int N = 1000;
    int D = 1024;
    MatrixXd X(N, D);
    VectorXd y(N);

    ifstream file("dataset_fft.csv");
    string line;
    int l=0;
    while (getline(file, line)) {
        int c = 0;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, '.')) {
            if (c<1024) X(l,c) = stod(cell);
            else y(l) = stod(cell);
            c++;
        }
        l++;
    }
    

    VectorXd mean = X.colwise().mean();
    VectorXd stddev = X.colwise().stddev();
    for (int i = 0; i < N; i++) {
        X.row(i) = (X.row(i) - mean).array() / stddev.array();
    }


    // Initialiser les poids du modèle
    VectorXd w = VectorXd::Zero(D);
    double b = 0.;

    // Définir la fonction coût et son gradient
    VectorXd grad(D);
    double cost = 0;
    for (int i = 0; i < N; i++) {
        double margin = y[i] * (X.row(i) * w + b);
        if (margin < 1) {
            cost += 1 - margin;
            grad += -y[i] * X.row(i).transpose();
        }
    }

    // Minimiser la fonction coût en utilisant un algorithme d'optimisation tel que la descente de gradient ou BFGS
    double learning_rate = 0.01;
    for (int t = 0; t < 1000; t++) {
        w = w - learning_rate * grad;
        b = b - learning_rate * grad.sum();

        // Recalculer la fonction coût et son gradient
        VectorXd grad(D);
        double cost = 0;
        for (int i = 0; i < N; i++) {
            double margin = y[i] * (X.row(i) * w + b);
            if (margin < 1) {
                cost += 1 - margin;
                grad += -y[i] * X.row(i).transpose();
            }
        }
    }

    // Stocker les poids du modèle optimisé
    

    return 0;
}
