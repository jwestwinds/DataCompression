//CHANGES/IMPROVEMENTS TO MAKE:
//
//GREAT, BUT DOESN'T GET LAST CHAR. FIX THIS.
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
    
    int bin; //code's binary equivilent
    
    int size; //# of bits in binary assignment
    
    char_lang(char i)
    :let(i)
    {
        bin = 0;
    }
    
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
vector<char_lang> newlang;
vector<char_freq> frequency;

void code2bit(char_lang &cl)
{
    int pow2 = 1;
    
    cl.size = cl.code.size();
    
    for(int i = cl.code.size() - 1; i >= 0; --i)
    {
        
        if(cl.code[i] == '1')
        {
            cl.bin = cl.bin+pow2;
        }
        pow2 = pow2*2;
    }
}


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

int bintoint(string bin)
{
    int it = 1;
    int to = 0;
    for(int i = 7; i >= 0 ; --i)
    {
        if(bin[i] == '1')
            to += it;
        
        it = it*2;
        
    }
    return to;
}

string inttobin(int rigbin)
{
    int obin = rigbin;
    int powa = 128;
    string bin = "";
    int frabin;
    
    if(obin >= 0)
    {
        while(bin.size() < 8)
        {
            if(obin - powa >= 0)
            {
                obin-=powa;
                bin+="1";
            }
            
            else
                bin+="0";
            
            powa = powa/2;
        }
    }
    
    else
    {
        obin = obin - 2*obin;
        obin = 256 - obin;
        
        while(bin.size() < 8)
        {
            if(obin - powa >= 0)
            {
                obin-=powa;
                bin+="1";
            }
            
            else
                bin+="0";
            
            powa = powa/2;
        }
    }
    
    return bin;
}

string intto8bin(int rigbin)
{
    int pow2 = pow(2, 15);
    string output = "";
    //cout << pow2;
    
    while(rigbin >= 0)
    {
        if(rigbin - pow2 >= 0)
        {
            output += "1" ;
            rigbin -= pow2;
        }
        
        else
            output += "0";
        
        if(pow2 ==1)
            break;
        pow2 = pow2/2;
    }
    
    return output;
    
}

string chartobin(char a)
{
    string strn = "";
    
    for (int i = 0; i < 8; i++)
    {
        int j = (a & (1 << (7 - i)));
        
        if(j==0)
            strn+="0";
        else
            strn+="1";
    }
    
    return strn;
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
        code2bit(language.at(j));
        cout << language.at(j).let << ", " << language.at(j).code << ", " << language.at(j).bin << ", " << language.at(j).size << endl;
    }
    
    
    //Calculate expected word length
    
    float exp = 0;
    for(int j = 0; j < frequency.size(); ++j)
        exp += (frequency.at(j).freq)*(language.at(j).code.size());
    
    exp = exp/word.size();
    
    cout << "EXPECTED CODEWORD LENGTH:\n" << exp << endl;
    cout << "LANGUAGE SIZE: " << language.size() << endl;

    ofstream filemyne;
    filemyne.open ("binary.cpp");
    
    //Make a vector of sizes for the codes
    vector<int> sizes;
    vector<int> sizefreq;
    
    for(int j = 0; j < language.size(); ++j)
    {
        int f = language.at(j).code.size();
        
        if(sizes.empty())
        {
            sizes.push_back(f);
            sizefreq.push_back(1);
        }
        else if(sizes.back() < f)
        {
            sizes.push_back(f);
            sizefreq.push_back(1);
        }
        else
        {
            sizefreq.back()++;
        }
    }
    
    string allcode = "";
    int alpha = language.size();
    
    string alphasize = intto8bin(alpha);
    
    cout << "INT REP OF ALPHASIZE:   " << alphasize << endl;
    //string alpha1 = alphasize.substr(0, 8);
    //alphasize.erase(0,8);
    //string alpha2 =alphasize;
    
    //int alphac = bintoint(alpha1);
    //char alpha1c = (char) alphac;
    
    //alphac = bintoint(alpha2);
    //char alpha2c = (char) alphac;
    
    //cout << alpha1c << alpha2c << endl;
    
    
    filemyne << alphasize; //fhqnilugefqiulwa vqtlwhvgaulVBHAETHQE
    for(int i = 0; i < alpha; ++i)
    {
        filemyne << inttobin((int)language.at(i).let);
    }
    
    for(int i = 0; i < sizes.size(); ++i)
    {
        string si = inttobin(sizes.at(i));
        string sf = inttobin(sizefreq.at(i));
        filemyne << si << sf;
    }
    
    for(int i = 0; i < alpha; ++i)
    {
        allcode += language.at(i).code;
    }
    
    while(allcode.size()%8 != 0)
    {
        allcode+="0";
    }
    
    cout << "ALL CODEWORDS: " << allcode << endl;
    string char_allcode = "";
    
    while(allcode!="")
    {
        string suball = allcode;
        suball.resize(8);
        int sublang = bintoint(suball);
        char charsublang = (char) sublang;
        char_allcode += charsublang;
        filemyne << suball;
        allcode.erase(0,8);
    }
    
    cout <<  "char rep of allcode: " << char_allcode << endl << endl;
    
    string codeword;
    
    if(argc > 1)
    {
        myfile.open(argv[1]);
        while(myfile.get(letter))
        {
            string fa = encode(letter);
            filemyne << fa;
        }
        myfile.close();
    }
    
    else
        for(int i = 0; i < size; ++i)
        {
            char chosen = word[i];
            string fa = encode(chosen);
            filemyne << fa;
        }
    
    filemyne.close();
    cout << "encode done";
    cout.flush();
    
    
    ////////////////conversion to char
    
    filemyne.open("char.cpp");
    myfile.open("binary.cpp");
    
    int placesadded = 0;
    char getter;
    string charrep = "";
    bool endf = false;
    
    while(!myfile.eof() && !endf)
    {
        
        charrep = "";
        for(int i = 0; i < 8; ++i)
        {
            myfile.get(getter);
            if(myfile.eof())
            {
                endf = true;
                break;
            }
            charrep+=getter;
            

        }
        
        if(charrep.size() < 8)
            while(charrep.size() != 8)
            {
                charrep += "0";
                placesadded++;
            }
        
        
        int binar = bintoint(charrep);
        
        char binchar = (char) binar;
        filemyne << binchar;
        
    }
    
    filemyne.close();
    myfile.close();
    
//    
//    //PART 3: Decoding Huffman's Algortithm
//
//    
//    myfile.open("char.cpp");
//    filemyne.open ("output.cpp");
//    
//    string binaa = "";
//    char la, ra, ga;
//    myfile.get(la);
//    int lar = (int) la;
//    cout << "THIS IS OUR LANGUAGE SIZE: " << lar << endl;
//    for(int i = 0; i < lar; ++i)
//    {
//        myfile.get(la);
//        char_lang a(la);
//        newlang.push_back(a);
//    }
//    
//    
//    //cout << "Here are the sizes of out codes: ";
//    int ls = 0;
//    int total_lang_size = 0;
//    while(ls < lar)
//    {
//        myfile.get(la); //size
//        myfile.get(ra); //number of times size occurs
//        int size_char = (int) la;
//        int num_size_char = (int) ra;
//        
//        for(int i = ls; i < ls+num_size_char; ++i)
//            newlang.at(i).size = size_char;
//        
//        total_lang_size += size_char*num_size_char;
//        ls+=num_size_char;
//    }
//    
//    cout << "Here is our language and the sizes of each codeword:" << endl;
//    for(int i = 0; i < newlang.size(); ++i)
//        cout << newlang.at(i).let << ", " << newlang.at(i).size << endl;
//    
//    string hallcode = "";
//    
//    while(hallcode.size()*8 < total_lang_size)
//    {
//        myfile.get(la);
//        hallcode+=la;
//    }
//    
//    string binhallcode = "";
//    
//    for(int i = 0; i < hallcode.size(); ++i)
//    {
//        binhallcode+= inttobin((int) hallcode.at(i));
//    }
//    
//    cout << "SHOULD BE EQUAL TO ALLCODE: " << binhallcode << endl;
//    
//    
//    for(int i = 0; i < newlang.size(); ++i)
//    {
//        string bhc = binhallcode;
//        bhc.resize(newlang.at(i).size);
//        //cout << bhc << endl;
//        newlang.at(i).code = bhc;
//        binhallcode.erase(0, bhc.size());
//    }
//    
//    cout << "NEW LANG:\n";
//    for(int j = 0; j < newlang.size(); ++j)
//        cout << newlang.at(j).let << ", " << newlang.at(j).code << ", " << newlang.at(j).size << endl;
//
//    
//    while(!myfile.eof())
//    {
//        
//        
//        while(binaa.size() < sizes.back())
//        {
//            myfile.get(letter);
//            int tho = (int)letter;
//            binaa += inttobin(tho);
//        }
//        
//        for(int j = 0; j < newlang.size(); ++j)
//        {
//            string binari = binaa;
//            binari.resize(newlang.at(j).code.size());
//            if(binari == newlang.at(j).code)
//            {
//                filemyne << newlang.at(j).let;
//                cout << newlang.at(j).let;
//                binaa.erase(0, newlang.at(j).code.size());
//                break;
//            }
//        }
//    }
//
//    filemyne.close();
//    myfile.close();
    return 0;
}