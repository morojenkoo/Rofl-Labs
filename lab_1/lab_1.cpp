#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>
#include <queue>
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

//рандомное правило в системе Т
int getRandomRule()
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<size_t> dist(0, T.size() - 1);
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

//до 10 случайных переписываний в системе Т
//получаем w->w1
string rewrite(string w)
{
    const int max_steps = 10;
    int steps = 0;
    while (steps < max_steps)
    {
        int num = getRandomRule();
        size_t index = w.find(T[num].first);
        if (index != string::npos)
            w.replace(index, T[num].first.length(), T[num].second);
        steps++;
    }
    return w;
}

//БФС для нахождения всех нормальных форм, потому что система не достроена до конца
unordered_set<string> findNormalForms(const string& start)
{
    unordered_set<string> normal_forms;
    queue<string> q;
    unordered_set<string> visited;
    q.push(start);
    visited.insert(start);
    while (!q.empty())
    {
        string current = q.front();
        q.pop();
        bool is_normal = true;
        for (const auto& rule : new_T)
        {
            size_t pos = current.find(rule.first);
            if (pos != string::npos)
            {
                is_normal = false;
                string next = current;
                next.replace(pos, rule.first.length(), rule.second);
                if (visited.find(next) == visited.end())
                {
                    visited.insert(next);
                    q.push(next);
                }
                //break;
            }
        }
        if (is_normal)
        {
            normal_forms.insert(current);
        }
    }
    
    return normal_forms;
}

//проверяем, что хотя бы одна нормальная форма совпала
bool fuzzing(string &w, string &w1)
{
    auto wNormalForms = findNormalForms(w);
    auto w1NormalForms = findNormalForms(w1);
    for (auto wNormalForm : wNormalForms)
    {
        if (w1NormalForms.find(wNormalForm) != w1NormalForms.end())
        {
            return true;
        }
    }
    cout << "w  = " << w << "\nw1 = " << w1 << endl;
    cout << "Normal forms of w:" << endl;
    for (auto nf : wNormalForms) {
        cout << "  " << nf << endl;
    }
    cout << "Normal forms of w1:" << endl;
    for (auto nf : w1NormalForms) {
        cout << "  " << nf << endl;
    }

    return false;
}

//длина строки 20, потому что если делать больше, то беда с временем работы
//чем больше строка, тем больше вариантов проверяем через бфс
//ничего не поделаешь, особенности варианта
int main()
{
    for (int i = 0; i < 1000; ++i)
    {
        string w = generateRandomString(20);
        string w1 = rewrite(w);
        bool fuzz = fuzzing(w, w1);
        if (fuzz) cout << "good" << endl;
        else
        {
            cout << "bad" << endl;
            break;
        }
    }
    return 0;
}