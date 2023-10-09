#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <utility>;

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY queries
 */

long arrayManipulationAlt(int n, vector<vector<int>> queries) {
    vector<long> arr(n, 0);
    for(vector<int> q : queries) { // a, b, k
        vector<long>::iterator begin = arr.begin() + q.at(0) - 1;
        vector<long>::iterator end = arr.begin() + q.at(1);
        for(vector<long>::iterator i = begin; i != end; ++i) {
            *i = *i + q.at(2);
        }
    }
    return *max_element(arr.begin(), arr.end());
}

long arrayManipulation(int n, vector<vector<int>> queries) {
    map<int, int> arr;
    arr.insert({1, 0});
    for(vector<int> q : queries) { // a, b, k
        map<int, int>::iterator it = arr.upper_bound(q.at(0));
        cout << "Query starting on: " << it->first << endl;
        if(it != arr.begin()) --it;
        int value = (it)->second;
        cout << "A - Insert " << value + q.at(2) << " at " << q.at(0) << endl;
        arr.insert_or_assign(q.at(0), value + q.at(2));
        while(it->first != q.at(0)) ++it;
        while(++it != arr.end() && (it)->first <= q.at(1)) {
            value = it->second;
            cout << "B - Insert " << value + q.at(2) << " at " << it->first << endl;
            arr.insert_or_assign(it->first, value + q.at(2));
        }
        cout << "C - Insert " << value << " at " << q.at(1) + 1 << endl;
        arr.insert_or_assign(q.at(1) + 1, value);
    }
    int max = 0;
    map<int, int>::iterator it = arr.begin();
    while( it != arr.end() && it->first < n) {
        if((++it)->second > max) {
            max = it->second;
        }
    }
    return max;
}

long arrayManipulationAlt2(int n, vector<vector<int>> queries) {
    map<int, int> arr;
    arr.insert({1, 0});
    int max = 0;
    for(vector<int> q : queries) { // a, b, k
        map<int, int>::iterator it = arr.upper_bound(q.at(0));
        if(it != arr.begin()) --it;
        int value = (it)->second;
        int summedValue = value + q.at(2);
        cout << "A - Insert " << value + q.at(2) << " at " << q.at(0) << endl;
        pair<map<int, int>::iterator, bool> res = arr.insert_or_assign(q.at(0), value + q.at(2));        
        if(summedValue > max) {
            max = summedValue;
        }
        it = res.first;
        while(++it != arr.end() && (it)->first <= q.at(1)) {
            value = it->second;
            summedValue = value + q.at(2);
            cout << "B - Insert " << summedValue << " at " << it->first << endl;
            arr.insert_or_assign(it->first, summedValue);
            if(summedValue > max) {
                max = summedValue;
            }
        }
        cout << "C - Insert " << value << " at " << q.at(1) + 1 << endl;
        arr.insert_or_assign(q.at(1) + 1, value);
    }
    return max;
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<vector<int>> queries(m);

    for (int i = 0; i < m; i++) {
        queries[i].resize(3);

        string queries_row_temp_temp;
        getline(cin, queries_row_temp_temp);

        vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int queries_row_item = stoi(queries_row_temp[j]);

            queries[i][j] = queries_row_item;
        }
    }

    long result = arrayManipulation(n, queries);

    cout << result << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](unsigned char c) { return !ispunct(c); })
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !ispunct(c); }).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
