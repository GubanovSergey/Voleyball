#include <fstream>
#include "world.h"
//TODO write class World with (essential) items:
/*
    World (Object * objs = NULL);
    Object * create_from_file(const fstream& world_config) //used to create list or array of objects
    move_constructor
*/

//TODO write class Timer with (essential) items:
/*
    double prec_;       //precision, step of in- or dec- reasing time
    double data_;
    Timer (double prec = 1, double init_val = 0):
    ....{}
*/

void simulation
(const fstream& world_config, int (is_simulation_closed *)(const World &, const Timer &)) {
    World voley (create_from_file(world_config)); //may be do this with try/catch blocks
    fstream log("logs\simulation.txt", ios_base::out);
    Timer timer(0.05);

    while(!is_simulation_closed(voley, time)) {
            //some very specific code

    }
}
