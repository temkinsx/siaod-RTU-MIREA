#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
using namespace std;

std::ofstream out("/Users/artem/Desktop/Универ/2 курс/3 сем/СИАОД/siaod-rtu-mirea/practice6/6.2/results.csv");

int substrLinearSearch(string &s, const string &pattern, long long &comparisons) {
    int n = s.size();
    int m = pattern.size();
    if (m > n) return -1;

    comparisons = 0;
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m) {
            comparisons++;
            if (s[i + j] != pattern[j]) break;
            j++;
        }
        if (j == m) {
            return i;
        }
    }
    return -1;
}

int boyerMooreHorspool(const std::string& text, const std::string& pattern, int start, long long &comparisons, long long &shifts) {
    std::unordered_map<char, int> table;
    int n = text.size();
    int m = pattern.size();

    if (m > n) return -1;

    shifts = 0;

    for (int i = 0; i < m - 1; i++) {
        table[pattern[i]] = m - i - 1;
    }

    int i = start;
    while (i <= n - m) {
        int j = m - 1;

        while (j >= 0) {
            comparisons++;
            if ( pattern[j] != text[i + j]) {
                break;
            }
            j--;
        }

        if (j < 0) {
            return i;
        }

        char c = text[i + m - 1];
        int shift = table.count(c) ? table[c] : m;
        i += shift;
        shifts++;
    }

    return -1;
}

int findLast(string &text, string &pattern) {
    int lastIndex = -1;
    long long cmp = 0, sh = 0;
    int pos = boyerMooreHorspool(text, pattern, 0, cmp, sh);
    while (pos != -1) {
        lastIndex = pos;
        pos = boyerMooreHorspool(text, pattern, pos + 1, cmp, sh);
    }
    return lastIndex;
}

#include <chrono>
#include <random>

string makeString(size_t n, const string &alphabet = "abcdefghijklmnopqrstuvwxyz") {
    std::mt19937_64 rng(1234567);
    std::uniform_int_distribution<int> dist(0, (int)alphabet.size() - 1);
    string s; s.reserve(n);
    for (size_t i = 0; i < n; ++i) s.push_back(alphabet[dist(rng)]);
    return s;
}

void printHeader() {
    out << "algorithm,n_text,m_pattern,case,found_index,success,comparisons,shifts,duration_us" << '\n';
}

void runLinear(const string &text, const string &pattern, const string &caseName) {
    long long cmp = 0;
    string t = text; // API expects non-const reference
    auto t0 = std::chrono::high_resolution_clock::now();
    int pos = substrLinearSearch(t, pattern, cmp);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    out << "linear" << ',' << text.size() << ',' << pattern.size() << ',' << caseName << ','
         << pos << ',' << (pos != -1) << ',' << cmp << ',' << 0 << ',' << us << '\n';
}

void runBMH(const string &text, const string &pattern, const string &caseName) {
    long long cmp = 0, sh = 0;
    auto t0 = std::chrono::high_resolution_clock::now();
    int pos = boyerMooreHorspool(text, pattern, 0, cmp, sh);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    out << "bmh" << ',' << text.size() << ',' << pattern.size() << ',' << caseName << ','
         << pos << ',' << (pos != -1) << ',' << cmp << ',' << sh << ',' << us << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    printHeader();

    // Small cases
    string small = "sdifjhsdf";
    runLinear(small, "fj", "small_mid_match");
    runBMH(small, "fj", "small_mid_match");
    runLinear(small, "sd", "small_start_match");
    runBMH(small, "sd", "small_start_match");
    runLinear(small, "df", "small_end_match");
    runBMH(small, "df", "small_end_match");
    runLinear(small, "zz", "small_no_match");
    runBMH(small, "zz", "small_no_match");

    // Repeated-character edge cases
    string repText = string(1000, 'a');
    string repPat1 = string(10, 'a');
    string repPat2 = string(10, 'b');
    runLinear(repText, repPat1, "repeated_all_match");
    runBMH(repText, repPat1, "repeated_all_match");
    runLinear(repText, repPat2, "repeated_no_match");
    runBMH(repText, repPat2, "repeated_no_match");

    // Larger randomized texts
    string text1e4 = makeString(10000);
    string pat10 = makeString(10);
    string pat50 = makeString(50);
    string pat200 = makeString(200);

    runLinear(text1e4, pat10, "n=1e4,m=10_rand");
    runBMH(text1e4, pat10, "n=1e4,m=10_rand");
    runLinear(text1e4, pat50, "n=1e4,m=50_rand");
    runBMH(text1e4, pat50, "n=1e4,m=50_rand");
    runLinear(text1e4, pat200, "n=1e4,m=200_rand");
    runBMH(text1e4, pat200, "n=1e4,m=200_rand");

    string text1e5 = makeString(100000);
    runLinear(text1e5, pat10, "n=1e5,m=10_rand");
    runBMH(text1e5, pat10, "n=1e5,m=10_rand");
    runLinear(text1e5, pat50, "n=1e5,m=50_rand");
    runBMH(text1e5, pat50, "n=1e5,m=50_rand");

    out.close();

    return 0;
}
