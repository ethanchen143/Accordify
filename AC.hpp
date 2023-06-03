#pragma once
#include "Packet.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void Parse3(const Packet& p, vector<vector<int>>& cp){
    string filename = "./data/three_chord_songs.csv";
    ifstream file(filename);
    if(!file.is_open()){
        cout << "Error opening file" << endl;
        return;
    }
    string line, field;
    vector<string> row;
    int first = 0;
    while (getline(file, line)) {
        if(first == 0){ // skip the first line
            first++;
            continue;
        }
        row.clear();
        stringstream ss(line);
        while (getline(ss, field, ',')) {
            row.push_back(field);
        }
        if(row[7] == "" || abs(stod(row[7]) - p.GetDancebility()) > 0.1) continue; //play around with the bound
        if(row[8] == "" || abs(stod(row[8]) - p.GetEnergy()) > 0.2) continue; // for better results
        if(row[16] == "" || abs(stod(row[16]) - p.GetValence()) > 0.2) continue;
        if(row[13] == "" || abs(stod(row[13]) - p.GetAcousticness()) > 0.5) continue;

        //add current chord prog.
        vector<int> tmp;
        tmp.push_back(static_cast<int>(row[0][1]) - '0');
        tmp.push_back(stoi(row[1]));
        tmp.push_back(static_cast<int>(row[2][0]) - '0');
        cp.push_back(tmp);
    }
}

void Parse4(const Packet& p, vector<vector<int>>& cp){
    string filename = "./data/four_chord_songs.csv";
    ifstream file(filename);
    if(!file.is_open()){
        cout << "Error opening file" << endl;
        return;
    }
    string line, field;
    vector<string> row;
    int first = 0;
    while (getline(file, line)) {
        if(first == 0){ // skip the first line
            first++;
            continue;
        }
        row.clear();
        stringstream ss(line);
        while (getline(ss, field, ',')) {
            row.push_back(field);
        }
        if(row[8] == "" || abs(stod(row[8]) - p.GetDancebility()) > 0.1) continue; //play around with the bound
        if(row[9] == "" || abs(stod(row[9]) - p.GetEnergy()) > 0.2) continue; // for better results
        if(row[17] == "" || abs(stod(row[17]) - p.GetValence()) > 0.2) continue;
        if(row[14] == "" || abs(stod(row[14]) - p.GetAcousticness()) > 0.5) continue;

        //add current chord prog.
        vector<int> tmp;
        tmp.push_back(static_cast<int>(row[0][1]) - '0');
        tmp.push_back(stoi(row[1]));
        tmp.push_back(stoi(row[2]));
        tmp.push_back(static_cast<int>(row[3][0]) - '0');
        cp.push_back(tmp);
    }
}

void Parse5(const Packet& p, vector<vector<int>>& cp){
    string filename = "./data/five_chord_songs.csv";
    ifstream file(filename);
    if(!file.is_open()){
        cout << "Error opening file" << endl;
        return;
    }
    string line, field;
    vector<string> row;
    int first = 0;
    while (getline(file, line)) {
        if(first == 0){ // skip the first line
            first++;
            continue;
        }
        row.clear();
        stringstream ss(line);
        while (getline(ss, field, ',')) {
            row.push_back(field);
        }
        if(row[9] == "" || abs(stod(row[9]) - p.GetDancebility()) > 0.1) continue; //play around with the bound
        if(row[10] == "" || abs(stod(row[10]) - p.GetEnergy()) > 0.2) continue; // for better results
        if(row[18] == "" || abs(stod(row[18]) - p.GetValence()) > 0.2) continue;
        if(row[15] == "" || abs(stod(row[15]) - p.GetAcousticness()) > 0.5) continue;

        //add current chord prog.
        vector<int> tmp;
        tmp.push_back(static_cast<int>(row[0][1]) - '0');
        tmp.push_back(stoi(row[1]));
        tmp.push_back(stoi(row[2]));
        tmp.push_back(stoi(row[3]));
        tmp.push_back(static_cast<int>(row[4][0]) - '0');
        cp.push_back(tmp);
    }
}

#include <map>
bool compare(const std::pair<int, double>& a, const std::pair<int, double>& b) {
    return a.second > b.second;
}

#include <random>
#include <exception>
//user input : a class (Packet) with variables
//the main function that takes in user input and return string data that can be used to make midi
    string Accordify(const Packet& p){
        //map chord to number
        map<int, string> chord_map;
        chord_map[1] = "Cmaj";
        chord_map[2] = "Dmin";
        chord_map[3] = "Emin";
        chord_map[4] = "Fmaj";
        chord_map[5] = "Gmaj";
        chord_map[6] = "Amin";
        chord_map[7] = "Bdim";

        vector<vector<int>> cp;
        if(p.GetFresh().size() == 3){
            Parse3(p,cp);
        } else if(p.GetFresh().size() == 4){
            Parse4(p,cp);
        } else {
            Parse5(p,cp);
        }
        
        cout<<cp.size()<<endl;
        if(cp.size() == 0){
            throw runtime_error("No song found");
        }
        string rt = "";
        for(unsigned j = 0; j < cp[0].size(); j++){
            map<int,int> frequency;
            for(unsigned i = 0; i < cp.size(); i++){
                if(frequency.find(cp[i][j]) == frequency.end()){
                    frequency[cp[i][j]] = 1;
                }
                else{
                    frequency[cp[i][j]]++;
                }
            }
            map<int,double> probability;
            for(auto& key : frequency){
                probability[key.first] = (double)key.second/cp.size();
            }
            vector<pair<int,double>> tosort(probability.begin(), probability.end());
            sort(tosort.begin(), tosort.end(), compare);
            //sort all the chord in an reverse order so that the more frequent chords are
            // more upfront
            for(auto& i : tosort){
                cout<<i.first<<" "<<i.second<<endl;
            }
            //select the chord with the proper freshness (the probability)
            int thechord = tosort[int(p.GetFresh()[j] * tosort.size() - 0.01)].first;
            if(thechord > 10){
                int firstdigit = thechord/10;
                int seconddigit = thechord%10;
                rt += chord_map[firstdigit];
                rt += " ";
                rt += chord_map[seconddigit];
                continue;
            } else {
                rt += chord_map[thechord];
            }

            std::random_device rd;
            std::default_random_engine gen(rd());
            string event1 = "7 ";
            string event2 = " ";
            // generate a random number between 0 and 1
            std::uniform_int_distribution<int> dist(0, 1);
            int rand_num = dist(gen);
            string chosen_event;
            //weighted - if valence is high (better mood), more likely to be major
            if (rand_num == 1) {
                chosen_event = event1;
            } else{
                chosen_event = event2;
            } 
            rt += chosen_event;
        }
        return rt;
    }
