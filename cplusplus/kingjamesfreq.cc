/*
 * Sample program to compare programming languages for my own edification.
 *
 * This program reads the KJV bible (from a fixed location) and computes the 
 * word frequency, printing the number of occurrences and frequency of the top
 * 25 words.
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>

using namespace std;

const size_t N_WORDS = 25;

typedef map<string, int> freqmap_t;

void add_freqs(string&, freqmap_t&);
void print_freqs(freqmap_t &freq_map);

int main()
{
    ifstream in;
    in.open("../data/kingjames.txt", ios::in);
    
    freqmap_t freq_map;
    string line;
    while (getline(in, line)) {
        add_freqs(line, freq_map);
    }
    in.close();

    print_freqs(freq_map);
}

const regex word_chars("\\w+");

void add_freqs(string &line, freqmap_t &freq_map)
{
    regex_iterator<string::iterator> it(line.begin(), line.end(), word_chars);
    regex_iterator<string::iterator> end;
    while (it != end) {
        string word(it->str());
        cout << word << endl;
        if (freq_map.find(word) == freq_map.end()) {
            freq_map[word] = 1;
        } else {
            freq_map[word]++;
        }
        it++;
    }
}

struct WordSum {
    int sum;
    WordSum() : sum(0) {}

    void operator() (const std::pair<string, int> &p)
    {
        sum += p.second;
    }
} word_sum;

typedef pair<string, int> entry;

struct EntryCmp {
    bool operator()(const entry &p1, const entry &p2)
    {
        return p1.second < p2.second;
    }
} entry_cmp;

void print_freqs(freqmap_t &freq_map)
{
    WordSum ws = for_each(freq_map.begin(), freq_map.end(), word_sum);
    int distinct_words = freq_map.size();

    cout << "Top " << N_WORDS << " words in the King James Bible" 
         << endl
         << "(Total words: " << ws.sum << "; " << distinct_words
         << " distinct words)"
         << endl;
    vector<entry> freq_list;
    for (freqmap_t::iterator it = freq_map.begin(); it != freq_map.end(); it++) {
        freq_list.push_back(*it);
    }

    sort(freq_list.begin(), freq_list.end(), entry_cmp);
    vector<entry>::iterator it = freq_list.begin();
    for (size_t i = 0; 
         i < N_WORDS; 
         i++, it++) 
    {
        entry e = *it;
        cout << e.first << " " << e.second << " ("
             << ((double)e.second)/ws.sum * 100.0
             << "%)"
             << endl;
    }
}
