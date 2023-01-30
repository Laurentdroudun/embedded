#include <iostream>
#include <Eigen/Core>
#include <Eigen/QR>

using namespace std;
using namespace Eigen;

int main() {
    // Charger les données d'entraînement
    MatrixXd X(N, D);
    VectorXd y(N);
    // ...

    VectorXd mean = X.colwise().mean();
    VectorXd stddev = X.colwise().stddev();
    for (int i = 0; i < N; i++) {
        X.row(i) = (X.row(i) - mean).array() / stddev.array();
    }


    // Initialiser les poids du modèle
    VectorXd w = VectorXd::Zero(D);
    double b = 0;

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
    // ...

    // Stocker les poids du modèle optimisé
    // ...

    return 0;
}
