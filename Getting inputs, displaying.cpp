struct Equation {
    vector<double> coefficients;
    double constant;
};

struct LinearProgram {
    vector<Equation> equations;
    vector<double> objectiveFunctionCoefficients;
};

void printTableau(const vector<vector<double>>& tableau) {
    for (const auto& row : tableau) {
        for (double val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
}

Equation getEquationFromUser(int numVariables) {
    Equation eq;
    cout << "Entrez les coefficients de l'équation (séparés par des espaces) : ";
    for (int i = 0; i < numVariables; ++i) {
        double coeff;
        cin >> coeff;
        eq.coefficients.push_back(coeff);
    }
    cout << "Entrez la constante de l'équation : ";
    cin >> eq.constant;

    return eq;
}

LinearProgram getUserInput() {
    LinearProgram lp;

    int numVariables;
    cout << "Entrez le nombre de variables : ";
    cin >> numVariables;

    int numEquations;
    cout << "Entrez le nombre d'équations : ";
    cin >> numEquations;

    cout << "Entrez les coefficients de la fonction objectif :" << endl;
    for (int i = 0; i < numVariables; ++i) {
        double coeff;
        cout << "Coefficient de la variable x" << (i + 1) << " : ";
        cin >> coeff;
        lp.objectiveFunctionCoefficients.push_back(coeff);
    }

    cout << "Entrez les contraintes :" << endl;
    for (int i = 0; i < numEquations; ++i) {
        Equation eq = getEquationFromUser(numVariables);
        lp.equations.push_back(eq);
    }

    return lp;
}
