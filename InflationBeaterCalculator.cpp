#include <bits/stdc++.h>
using namespace std;

struct Investment {
    string name;
    double initialValue;
    double finalValue;

    int firstYear;
    int yearsHeld;

    double inflationCAGR;
    double nominalCAGR;
    double realCAGR;

    bool beatsInflation;
    vector<double> inflationRates;
};

/* ===== FUNCTIONS ===== */

double computeInflationCAGR(const vector<double>& rates) {
    double product = 1.0;
    for (double r : rates) {
        product *= (1.0 + r);
    }
    return (pow(product, 1.0 / rates.size()) - 1.0) * 100.0;
}

double computeNominalCAGR(double initialValue, double finalValue, int years) {
    return (pow(finalValue / initialValue, 1.0 / years) - 1.0) * 100.0;
}

/* ===== MAIN ===== */

int main() {
    vector<Investment> investments;
    char tryAgain;
    int currentYear;

    cout << "What year is it right now?: ";
    cin >> currentYear;

    do {
        Investment inv;
        vector<double> inflationRates;

        cout << "\nSince when did you start investing this instrument?: ";
        cin >> inv.firstYear;

        inv.yearsHeld = currentYear - inv.firstYear;

        for (int i = 0; i < inv.yearsHeld; i++) {
            double rate;
            cout << "Enter inflation rate for year " << inv.firstYear + i << " (%): ";
            cin >> rate;
            inflationRates.push_back(rate / 100.0);
        }

        inv.inflationRates = inflationRates;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter the name of the investment: ";
        getline(cin, inv.name);

        cout << "Input its initial value: ";
        cin >> inv.initialValue;

        cout << "Input its current value: ";
        cin >> inv.finalValue;

        inv.nominalCAGR = computeNominalCAGR(
            inv.initialValue,
            inv.finalValue,
            inv.yearsHeld
        );

        inv.inflationCAGR = computeInflationCAGR(inv.inflationRates);
        inv.realCAGR = inv.nominalCAGR - inv.inflationCAGR;
        inv.beatsInflation = (inv.realCAGR >= 0);

        investments.push_back(inv);

        cout << "\nWanna add another investment? (y/n): ";
        cin >> tryAgain;

    } while (tryAgain == 'y' || tryAgain == 'Y');

    /* ===== OUTPUT ===== */

    cout << fixed << setprecision(2);

    for (const auto& inv : investments) {
        cout << "\n===================== INVESTMENT SUMMARY =====================\n";
        cout << "Name: " << inv.name << endl;
        cout << "Holding Period: " << inv.yearsHeld << " years\n";
        cout << "Initial Value: " << inv.initialValue << endl;
        cout << "Final Value: " << inv.finalValue << endl;

        cout << "Inflation CAGR: " << inv.inflationCAGR << "%\n";
        cout << "Nominal CAGR: " << inv.nominalCAGR << "%\n";
        cout << "Real CAGR: " << inv.realCAGR << "%\n";

        cout << "Annual Inflation Rates:\n";
        for (int i = 0; i < inv.yearsHeld; i++) {
            cout << inv.firstYear + i << ": "
                 << inv.inflationRates[i] * 100 << "%\n";
        }

        cout << "Beats Inflation? "
             << (inv.beatsInflation ? "YES" : "NO") << endl;
    }

    /* ===== PREVENT CMD FROM CLOSING ===== */
    cout << "\nPress ENTER to exit...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    return 0;
}
