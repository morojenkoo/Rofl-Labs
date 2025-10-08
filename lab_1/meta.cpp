#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>
using namespace std;
const string alphabet = "abc";
const vector<pair<string, string>> T =
{
    make_pair("abca", "aaaa"),
    make_pair("bcab", "bbbb"),
    make_pair("cabc", "cccc"),
    make_pair("abc", "aaa"),
    make_pair("abc", "bbb"),
    make_pair("abc", "ccc"),
    make_pair("aabbcc", "abcabc"),
};
const vector<pair<string, string>> new_T =
{
    make_pair("bcab", "baaa"),
    make_pair("abc", "aaa"),
    make_pair("aabbcc", "aaaaaa"),
    make_pair("bbb", "aaa"),
    make_pair("ccc", "aaa"),
    make_pair("aaab", "baaa"),
    make_pair("aaac", "caaa"),
    make_pair("bcaaa", "aaaaa"),
    make_pair("ccaaa", "abaaa"),
    make_pair("cabaaa", "aaaaaa"),
    make_pair("caaaaaa", "aabbaaa"),
};

//рандомное правило в системе new_Т
int getRandomRule()
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<size_t> dist(0, new_T.size() - 1);
    return dist(gen);
}

string generateRandomString(int n)
{
    string s;
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<size_t> dist(0, alphabet.size() - 1);
    for (int i = 0; i < n; ++i){
        s += alphabet[dist(gen)];
    }
    return s;
}

//до 10 случайных переписываний в системе new_Т
//получаем w->w1
string rewrite(string w)
{
    const int max_steps = 10;
    int steps = 0;
    while (steps < max_steps)
    {
        int num = getRandomRule();
        size_t index = w.find(new_T[num].first);
        if (index != string::npos)
            w.replace(index, new_T[num].first.length(), new_T[num].second);
        steps++;
    }
    return w;
}

int countLetters(const string& s) 
{
    int count_b = 0;
    int count_c = 0;
    for (char c : s) {
        if (c == 'b') count_b++;
        else if (c == 'c') count_c++;
    }
    return (count_b + 2 * count_c) % 3;
}

bool meta(string &w, string &w1)
{
    if (w.size() == w1.size() && countLetters(w1) == countLetters(w))
        return true;
    else
    {
        cout << "w  = " << w << " w.size  = " << w.size() << " letters = " << countLetters(w) << endl;
        cout << "w1 = " << w1 << " w1.size = " << w1.size() << " letters = " << countLetters(w1) << endl;
        return false;
    }
}
int main()
{
    for (int i = 0; i < 1000; ++i)
    {
        string w = generateRandomString(1000);
        string w1 = rewrite(w);
        bool metat = meta(w, w1);
        if (metat) cout << "good" << endl;
        else
        {
            cout << "bad" << endl;
            break;
        }
    }
    return 0;
}