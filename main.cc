#include "AC.hpp"
#include "Packet.hpp"

int main(){
    Packet p;
    p.SetDancebility(0.7);
    p.SetEnergy(0.8);
    p.SetValence(0.3);
    p.SetAcousticness(0.1);
    p.SetFresh(1);
    p.SetFresh(0.3);
    p.SetFresh(1);
    p.SetFresh(0.6);
    cout<<Accordify(p)<<endl;
    return 0;
}