#pragma once
#include <string>
#include <vector>
using namespace std;

class Packet{
    public:

    Packet(){
        dancebility = 0;
        energy = 0;
        valence = 0;
        acousticness = 0;}

    void SetDancebility(double dancebility){this->dancebility = dancebility;}
    void SetEnergy(double energy){this->energy = energy;}
    void SetValence(double valence){this->valence = valence;}
    void SetAcousticness(double acousticness){this->acousticness = acousticness;}

    double GetDancebility() const {return dancebility;}
    double GetEnergy() const {return energy;}
    double GetValence() const {return valence;}
    double GetAcousticness() const {return acousticness;}

    void SetFresh(double tmp){fresh.push_back(tmp);}
    vector<double> GetFresh() const{return fresh;}

    private:
    
    double dancebility; //dance
    double energy; //energy
    double valence; //mood
    double acousticness; //acousticness
    vector<double> fresh;
};