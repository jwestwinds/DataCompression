//
//  datacomp.cpp
//  Assignment1
//
//  Created by James Westcott on 4/16/15.
//  Copyright (c) 2015 James Westcott. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

struct char_lang
{
    char let;
    string code;
    
};

struct char_freq
{
    vector<char> lets;
    int freq;
    
};

int main()
{
    string word;
    
    cin >> word;
    
    cout << word;
    
    return 0;
}