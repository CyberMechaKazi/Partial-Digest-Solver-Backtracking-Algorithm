// Partial Digest (refactored, unique structure)
// Build: g++ -std=c++17 -O2 main.cpp -o Prog2
// Run:   ./Prog2 <input_file>
// my program uses "pdp_input_sample.txt" which has L = { 2 3 3 3 4 5 6 6 7 7 8 9 10 10 11 12 14 14 17 17 20 } but you need to give your file name or path location
// Output: Prog2-output.txt display total 8X duplicates output

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <cstdlib> // abs()
#include <functional> // at top for 'greater'

using namespace std;

class PartialDigestSolver {
public:
    explicit PartialDigestSolver(const string& input_path)
    // you need to change the input file here
        : input_path_("pdp_input_sample.txt"), out_("Prog2-output.txt") {}

    bool run() {
        if (!readDistances()) return false;
        if (distances_.empty()) return this->writeNoSolutions();

        // D = max distance. Remove one copy (distance between 0 and D).
        width_ = *max_element(distances_.begin(), distances_.end());
        auto it = find(distances_.begin(), distances_.end(), width_);
        if (it == distances_.end()) return this->writeNoSolutions();
        distances_.erase(it);

        placed_.clear();
        placed_.push_back(0);
        placed_.push_back(width_);

        backtrack();

        for (const auto& sol : solutions_) {
            out_ << "X = { ";
            for (size_t i = 0; i < sol.size(); ++i) {
                out_ << sol[i] << (i + 1 == sol.size() ? " " : ", ");
            }
            out_ << "}" << '\n';
        }
        return true;
    }

private:
    // ---------- Data ----------
    string input_path_;
    vector<int> distances_;
    vector<int> placed_;
    int width_ = 0;
    // set<vector<int>, greater<vector<int>>> solutions_; // changed here
    vector<vector<int>> solutions_;
    ofstream out_;

    // ---------- I/O ----------
    // Tolerant reader: ignores non-digit chars like L, =, {, }, commas
    bool readDistances() {
        ifstream in(input_path_);
        if (!in) {
            cerr << "Error: cannot open input file: " << input_path_ << '\n';
            return false;
        }
        string tok;
        while (in >> tok) {
            string clean;
            clean.reserve(tok.size());
            for (char c : tok) {
                if (c == '-' || (c >= '0' && c <= '9')) clean.push_back(c);
            }
            if (!clean.empty() && clean != "-" && clean != "+") {
                distances_.push_back(stoi(clean));
            }
        }
        sort(distances_.begin(), distances_.end());
        if (distances_.empty()) {
            cerr << "Error: no integers found in file (check formatting).\n";
            return false;
        }
        return true;
    }

    bool writeNoSolutions() {
        out_ << "No solutions found.\n";
        return false;
    }

    // ---------- Helpers ----------
    vector<int> diffsFrom(int y) const {
        vector<int> diffs;
        diffs.reserve(placed_.size());
        for (int x : placed_) diffs.push_back(abs(y - x));
        return diffs;
    }

    bool hasAll(const vector<int>& need) const {
        vector<int> temp = distances_;
        for (int v : need) {
            auto it = find(temp.begin(), temp.end(), v);
            if (it == temp.end()) return false;
            temp.erase(it);
        }
        return true;
    }

    void removeAll(const vector<int>& need) {
        for (int v : need) {
            auto it = find(distances_.begin(), distances_.end(), v);
            if (it != distances_.end()) distances_.erase(it);
        }
    }

    void restoreAll(const vector<int>& need) {
        for (int v : need) distances_.push_back(v);
        sort(distances_.begin(), distances_.end());
    }

    void recordSolution() {
        vector<int> sortedX = placed_;
        sort(sortedX.begin(), sortedX.end());
        solutions_.push_back(sortedX);   // keep duplicates
    }


    // ---------- Core backtracking ----------
    void backtrack() {
        if (distances_.empty()) { recordSolution(); return; }
        int y = distances_.back(); // since distances_ is sorted
        tryPlace(y);
        tryPlace(width_ - y);
    }

    void tryPlace(int candidate) {
        auto need = diffsFrom(candidate);
        if (!hasAll(need)) return;
        placed_.push_back(candidate);
        removeAll(need);
        backtrack();
        restoreAll(need);
        placed_.pop_back();
    }
};

int main(int argc, char** argv) {
    // Default to sample file if no argument is given
    string path = (argc == 2) ? string(argv[1]) : string("pdp_input_sample.txt");
    PartialDigestSolver solver(path);
    solver.run();
    return 0;
}
