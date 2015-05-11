//
//  decomp.cpp
//  
//
//  Created by James Westcott on 5/7/15.
//
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
    for(int i = bin.size() - 1; i >= 0 ; --i)
    {
        cout << "bin rep & increm: " << bin[i] << " " << it << endl;
        
        if(bin[i] == '1')
        {
            to += it;
            
        }
        
        it = it*2;
        
        cout << to << endl;
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
        {
            output += "0";
        }
        
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
    string charfile;
    
    if(argc == 1)
    {
        charfile = "char.cpp";
        cout << "No file to decompress" << endl;
        return 0;
    }
    
    else
        charfile = argv[1];
    
    string word; //input
    unsigned long size; //size of word
    
    char letter;
    
    ifstream myfile;
    ofstream filemyne;
    
    myfile.open(charfile);
    filemyne.open ("output.png");

    string binaa = "";
    char la, al, ra, ga;
    int lsiz;
    myfile.get(la);
    cout << la;
    myfile.get(al);
    cout << al;
    
    cout << la << al;
    
    string las = chartobin(la);
    string als = chartobin(al);
    cout << las;
    cout << als;
    string lasals = las+als;
    
    int lar = bintoint(lasals);
    //int lar = (int) la;
    cout << "THIS IS OUR LANGUAGE SIZE: " << lar << endl;
    for(int i = 0; i < lar; ++i)
    {
        myfile.get(la);
        char_lang a(la);
        newlang.push_back(a);
    }


    //cout << "Here are the sizes of out codes: ";
    int ls = 0;
    int total_lang_size = 0;

    while(ls < lar)
    {
        myfile.get(la); //size
        
        myfile.get(ra); //number of times size occurs
        int size_char = (int) la;
        
        
        int num_size_char = (int) ra;
        
        for(int i = ls; i < ls+num_size_char; ++i)
            newlang.at(i).size = size_char;
        
        total_lang_size += size_char*num_size_char;

        ls+=num_size_char;
    }

    cout << "Here is our language and the sizes of each codeword:" << endl;
    for(int i = 0; i < newlang.size(); ++i)
    {
        cout << newlang.at(i).let << ", " << newlang.at(i).size << endl;
    }
    string hallcode = "";

    while(hallcode.size()*8 < total_lang_size)
    {
        myfile.get(la);
        hallcode+=la;
    }

    string binhallcode = "";

    for(int i = 0; i < hallcode.size(); ++i)
    {
        binhallcode+= inttobin((int) hallcode.at(i));
    }

    cout << "SHOULD BE EQUAL TO ALLCODE: " << binhallcode << endl;
    cout.flush();
    
    


    for(int i = 0; i < newlang.size(); ++i)
    {
        string bhc = binhallcode;
        bhc.resize(newlang.at(i).size);
        //cout << bhc << endl;
        newlang.at(i).code = bhc;
        binhallcode.erase(0, bhc.size());
    }

    cout << "NEW LANG:\n";
    for(int j = 0; j < newlang.size(); ++j)
    cout << newlang.at(j).let << ", " << newlang.at(j).code << ", " << newlang.at(j).size << endl;
    
    
    vector<int> sizes;
    vector<int> sizefreq;
    
    for(int j = 0; j < newlang.size(); ++j)
    {
        int f = newlang.at(j).code.size();
        
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



    while(!myfile.eof())
    {
        //cout << binaa.size() << ", " << sizes.back() << endl;
        //cout.flush();
        
        while(binaa.size() < sizes.back())
        {
            //cout << "LAR" << "endl";
            //cout.flush();
            myfile.get(letter);
            //if(myfile.eof())
            //{
            //    break;
            //}
            int tho = (int)letter;
            binaa += inttobin(tho);
        }
        
        for(int j = 0; j < newlang.size(); ++j)
        {
            string binari = binaa;
            binari.resize(newlang.at(j).code.size());
            if(binari == newlang.at(j).code)
            {
                filemyne << newlang.at(j).let;
                cout << newlang.at(j).let;
                binaa.erase(0, newlang.at(j).code.size());
                break;
            }
        }
    }

    filemyne.close();
    myfile.close();
    return 0;
}
