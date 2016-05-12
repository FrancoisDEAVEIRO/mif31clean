#include "../../include/pavage.hpp"
#include "../../include/simplexe.hpp"
#include "../../include/createFile.hpp"
#include "../../include/reader.hpp"
#include <Grapic.h>
#include <string>

using namespace grapic;

const int DIMW = 800;
const int infoSize = 150;

struct Data
{
    int n;
};

void init(Data& d)
{
    d.n = 10;
}

int main(int , char** )
{
    bool stop=false;
	winInit("MyProg", DIMW, DIMW+infoSize);
    setKeyRepeatMode(false);
    CreateFilePointRandom(2, DIMW, 10);
    std::vector<Point<int,2> > nuageDePoints;
    nuageDePoints = lecture<int,2>("data/pointRandom2D.txt");

	Pavage<int,2> pavage(nuageDePoints,DIMW);
	//pavage.affiche();
    pavage.displayInfo("info","info","info", DIMW, infoSize);

	while( !stop ){
        backgroundColor( 100, 50, 200 );
        pavage.drawPavage(DIMW,infoSize);
        stop = winDisplay();
    }
    //winQuit();
	return 0;
}

