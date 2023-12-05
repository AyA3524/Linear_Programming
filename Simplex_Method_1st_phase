struct SimplexTableau {
    vector<vector<double>> tableau;
};

void printSimplexTableau(const SimplexTableau& simplexTableau) {
    for (const auto& row : simplexTableau.tableau) {
        for (double val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
}

int findEnteringColumn(const SimplexTableau& simplexTableau) {
    const vector<double>& objectiveRow = simplexTableau.tableau.back();
    auto minCoeffIt = min_element(objectiveRow.begin(), objectiveRow.end() - 1);
    return distance(objectiveRow.begin(), minCoeffIt);
}

int findLeavingRow(const SimplexTableau& simplexTableau, int enteringColumn) {
    int numRows = simplexTableau.tableau.size() - 1;
    int leavingRow = -1;
    double minRatio = numeric_limits<double>::max();

    for (int i = 0; i < numRows; ++i) {
        if (simplexTableau.tableau[i][enteringColumn] > 0) {
            double ratio = simplexTableau.tableau[i].back() / simplexTableau.tableau[i][enteringColumn];
            if (ratio < minRatio) {
                minRatio = ratio;
                leavingRow = i;
            }
        }
    }

    return leavingRow;
}

void pivot(SimplexTableau& simplexTableau, int enteringColumn, int leavingRow) {
    int numRows = simplexTableau.tableau.size();
    int numCols = simplexTableau.tableau[0].size();

    for (int i = 0; i < numRows; ++i) {
        if (i != leavingRow) {
            double ratio = simplexTableau.tableau[i][enteringColumn] / simplexTableau.tableau[leavingRow][enteringColumn];
            for (int j = 0; j < numCols; ++j) {
                simplexTableau.tableau[i][j] -= ratio * simplexTableau.tableau[leavingRow][j];
            }
        }
    }

    double pivotElement = simplexTableau.tableau[leavingRow][enteringColumn];
    for (int j = 0; j < numCols; ++j) {
        simplexTableau.tableau[leavingRow][j] /= pivotElement;
    }
}

bool isOptimal(const SimplexTableau& simplexTableau) {
    const vector<double>& objectiveRow = simplexTableau.tableau.back();
    return all_of(objectiveRow.begin(), objectiveRow.end() - 1, [](double val) { return val >= 0; });
}

SimplexTableau initializeSimplexTableau(const LinearProgram& lp) {
    SimplexTableau simplexTableau;

    // Copy coefficients from the linear program
    for (const auto& eq : lp.equations) {
        simplexTableau.tableau.push_back(eq.coefficients);
        simplexTableau.tableau.back().push_back(eq.constant);
    }

    // Add slack variables
    for (int i = 0; i < simplexTableau.tableau.size(); ++i) {
        for (int j = 0; j < simplexTableau.tableau.size(); ++j) {
            simplexTableau.tableau[i].push_back((i == j) ? 1.0 : 0.0);
        }
    }

    // Add coefficients of the objective function
    simplexTableau.tableau.push_back(lp.objectiveFunctionCoefficients);
    simplexTableau.tableau.back().insert(simplexTableau.tableau.back().end(), simplexTableau.tableau[0].size() - 1, 0.0);  // Add zeros for slack variables

    return simplexTableau;
}

void simplexAlgorithm(SimplexTableau& simplexTableau) {
    while (!isOptimal(simplexTableau)) {
        int enteringColumn = findEnteringColumn(simplexTableau);
        int leavingRow = findLeavingRow(simplexTableau, enteringColumn);

        if (leavingRow == -1) {
            cout << "The problem is unbounded." << endl;
            return;
        }

        pivot(simplexTableau, enteringColumn, leavingRow);

        cout << "Tableau after iteration:" << endl;
        printSimplexTableau(simplexTableau);
    }

    cout << "Optimal solution found." << endl;
}
