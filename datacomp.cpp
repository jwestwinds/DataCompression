//CHANGES/IMPROVEMENTS TO MAKE:
//
// *make able to read in spacebar
// *add file input capability
// *try with grouping : 2, 3 letters, words
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

using namespace std;

//each character in language with it's code
struct char_lang
{
    char let; //character in language
    
    string code; //Binary assignment
    
    char_lang(char i)
    :let(i)
    {}
    
};

//Frequency of letters and their eveuntual probability
struct char_freq
{
    vector<char> lets; //characters in present probability
    
    int freq; //how many times it occurs
    
    char_freq()
    {}
    
    char_freq(char i)
    {
        lets.push_back(i);
        freq = 1;
    }
    
    char_freq(char i, int f)
    {
        lets.push_back(i);
        freq = f;
    }
    
};

vector<char_lang> language;
vector<char_freq> frequency;


int ext_max(vector<char_freq> inp)
{
    int max = 0;
    int index = 0;
    
    for(int j = 0; j < inp.size(); ++j)
        if(inp.at(j).freq > max)
        {
            max = inp.at(j).freq;
            index = j;
        }
    
    return index;
    
}

vector<char_freq> sort(vector<char_freq> inp)
{
    vector<char_freq> oup;
    
    while(inp.size() != oup.size())
    {
        int ind = ext_max(inp);
        oup.push_back(inp.at(ind));
        inp.at(ind).freq = -1;
    }
    
    return oup;
}

string encode(char c)
{
    for(int i = 0; i < language.size(); ++i)
    {
        if(c == language.at(i).let)
            return language.at(i).code;
    }
    
    return "";
}


int main(int argc, char *argv[])
{
    string word; //input
    unsigned long size; //size of word
    
    char letter;
    
    cout << argc;
    
    ifstream myfile;
    
    if(argc > 1)
    {
        string filedat = argv[1];
        myfile.open(argv[1]);
        
        while(myfile.get(letter))
        {
            size++;
            word += letter;
            bool in_lang = false;
            
            
            for(int j = 0; j < language.size(); ++j)
                if(language.at(j).let == letter)
                {
                    in_lang = true;
                    frequency.at(j).freq = frequency.at(j).freq + 1;
                }
            
            
            if(!in_lang)
            {
                char_lang a(letter);
                char_freq b(letter);
                language.push_back(a);
                frequency.push_back(b);
            }

        }
        
        myfile.close();
        
    }
    
    
    else
    {
    
        cin.clear();
        cin >> word;
        size = word.size();
        
        
        
        
        // PART 1: Parsing the input and filling our language as well as tracking our frequencies
        
        for(int i = 0; i < size; ++i)
        {
            char chosen = word[i];
            bool in_lang = false;
            
            
            for(int j = 0; j < language.size(); ++j)
                if(language.at(j).let == chosen)
                {
                    in_lang = true;
                    frequency.at(j).freq = frequency.at(j).freq + 1;
                }
            
            
            if(!in_lang)
            {
                char_lang a(chosen);
                char_freq b(chosen);
                language.push_back(a);
                frequency.push_back(b);
            }
            
            
            
        }
    }
    
    cout << "FREQ:\n";
    for(int j = 0; j < frequency.size(); ++j)
        cout << frequency.at(j).lets.at(0) << ", " << frequency.at(j).freq << endl;
    
    // PART 2: Huffman Algorithm
    
    //First we sort our arrays
    
    vector<char_freq> s_freq;
    
    s_freq = sort(frequency);
    frequency = s_freq;
    
    cout << "SORTED FREQ:\n";
    for(int j = 0; j < s_freq.size(); ++j)
        cout << s_freq.at(j).lets.at(0) << ", " << s_freq.at(j).freq << endl;
    
    //Now for our language
    
    for(int j = 0; j < language.size(); ++j)
        language.at(j).let = s_freq.at(j).lets.at(0);
    
    cout << "LANG:\n";
    for(int j = 0; j < language.size(); ++j)
        cout << language.at(j).let << endl;
    
    //Probability time
    //Let's pop the last two elements
    int step = 1;
    while(s_freq.size() > 1)
    {
        
        
        char_freq min1 = s_freq.back();
        s_freq.pop_back();
        char_freq min2 = s_freq.back();
        s_freq.pop_back();
        
        /*cout << "2 min popped:\n";
         
         for(int j = 0; j < s_freq.size(); ++j)
         cout << s_freq.at(j).lets.at(0) << ", " << s_freq.at(j).freq << endl;*/
        
        char_freq min3;
        min3.freq = min1.freq + min2.freq;
        
        for(int j = 0; j < min1.lets.size(); ++j)
        {
            //search lang for elements in min1, if found, add 1 to that char's code
            for(int k = 0; k < language.size(); ++k)
                if(language.at(k).let == min1.lets.at(j))
                    language.at(k).code="1"+language.at(k).code;
            
            //push it onto min3
            min3.lets.push_back(min1.lets.at(j));
        }
        
        for(int j = 0; j < min2.lets.size(); ++j)
        {
            //search lang for elements in min2, if found, add 0 to that char's code
            for(int k = 0; k < language.size(); ++k)
                if(language.at(k).let == min2.lets.at(j))
                    language.at(k).code="0"+language.at(k).code;
            
            
            //push it onto min3
            min3.lets.push_back(min2.lets.at(j));
        }
        
        //push it onto s_freq and re-sort
        s_freq.push_back(min3);
        s_freq = sort(s_freq);
        
    }
    
    //If only 1 letter in language
    if(language.size() == 1)
        language.at(0).code="1";
    
    cout << "NEW LANG:\n";
    for(int j = 0; j < language.size(); ++j)
    {
        cout << language.at(j).let << ", " << language.at(j).code << endl;
    }
    
    
    //Calculate expected word length
    
    float exp = 0;
    for(int j = 0; j < frequency.size(); ++j)
    {
        exp += (frequency.at(j).freq)*(language.at(j).code.size());
    }
    
    exp = exp/word.size();
    
    cout << "EXPECTED CODEWORD LENGTH:\n" << exp << endl;

    
    
    ofstream filemyne;
    filemyne.open ("test0.txt");
    
    
    cout.flush();
    
    
    
    string codeword;
    
    if(argc > 1)
    {
        myfile.open(argv[1]);
        
        while(myfile.get(letter))
            filemyne << encode(letter);
        
        myfile.close();
        
    }
    

    
    else
        for(int i = 0; i < size; ++i)
        {
            char chosen = word[i];
            filemyne << encode(chosen);
        }
    
    filemyne.close();
    cout << "encode done";
    cout.flush();
    
    

//    
//    
//    //PART 3: Decoding Huffman's Algortithm
//    
//    
//
//    
    //Make a vector of sizes for the codes
    vector<int> sizes;
    
    for(int j = 0; j < language.size(); ++j)
    {
        int f = language.at(j).code.size();
        
        if(sizes.empty())
            sizes.push_back(f);
        else if(sizes.back() < f)
            sizes.push_back(f);
    }

    //Start decoding
    
    string newword;
    string sub_code;
    int cursize;
    
    myfile.open("test0.txt");
    filemyne.open ("test55.mp3");
    
    bool lettergot = false;
    int index = 0;
    
    while(!myfile.eof())
    {
        lettergot = false;
        cout << index++;
        
        while(!myfile.eof())
        {
            myfile.get(letter);
            newword+=letter;
            
            for(int j = 0; j < language.size(); ++j)
                if(language.at(j).code == newword)
                {
                    filemyne << language.at(j).let;
                    lettergot = true;
                    cout << language.at(j).let;
                    newword = "";
                    break;
                }
        }
    }

    myfile.close();
    filemyne.close();
    
    return 0;
}