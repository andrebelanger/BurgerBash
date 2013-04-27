// Burger Bash
#include "cubetypes.h"

#include <sifteo.h>
#include "assets.gen.h"
using namespace Sifteo;

static const unsigned gNumCubes = 3;
Random gRandom;

static AssetSlot MainSlot = AssetSlot::allocate()
    .bootstrap(GameAssets);

static Metadata M = Metadata()
    .title("Burger Bash")
    .package("", "1.0")
    .icon(Icon)
    .cubeRange(gNumCubes);

/* Array of cubes. Global because it's needed in multiple places, and the Sifteo SDK
 does not like passing instances of our custom class as parameters. Not heap-allocated
 (e.g., using keyword 'new') because the SDK does not like that either. */
// -----------------------------------
static BurgerBashCube cubes[gNumCubes];
static PlateCube pCube;
// ------------------------------------

// This class CAN see the cubes array
class EventHandler{
public:
	void init()
	{
		Events::cubeTouch.set(&EventHandler::onTouch, this);
		
		Events::neighborAdd.set(&EventHandler::onNeighborAdd, this);
        Events::neighborRemove.set(&EventHandler::onNeighborRemove, this);
        //Events::cubeAccelChange.set(&SensorListener::onAccelChange, this);
        //Events::cubeBatteryLevelChange.set(&SensorListener::onBatteryChange, this);
        //Events::cubeConnect.set(&SensorListener::onConnect, this);

	}

	void onTouch(unsigned id)
	{
		if(id < gNumCubes-1)
		{
			cubes[id].changeImage();
		}
	}
	
	void onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
    {
        //LOG("Neighbor Add: %02x:%d - %02x:%d\n", firstID, firstSide, secondID, secondSide);

		// Give the image from the ingredient cube to the plate cube
		if(firstID == pCube.cube)
		{
			pCube.changeImage(cubes[secondID].getImage());
		}
		else if(secondID == pCube.cube)
		{
			pCube.changeImage(cubes[firstID].getImage());
		}
    }
	
	void onNeighborRemove(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
    {
        //LOG("Neighbor Remove: %02x:%d - %02x:%d\n", firstID, firstSide, secondID, secondSide);

        if (firstID < arraysize(cubes)) {
            //counters[firstID].neighborRemove++;
            //drawNeighbors(firstID);
        }
        if (secondID < arraysize(cubes)) {
            //counters[secondID].neighborRemove++;
            //drawNeighbors(secondID);
        }
    }
};


void main()
{
	LOG("Burger Bash running on the Sifteo SDK\n");
	
	EventHandler eventHandler;
	eventHandler.init();
	
	// Plate cube initialize
	pCube.init(gNumCubes - 1);
	
	// Init all other cubes
	for (int i = 0; i < gNumCubes - 1; i++)
	{
		cubes[i].init(i);
	}
	
	// Game loop
	TimeStep ts;
    while (1) {
		for (int i = 0; i < gNumCubes; i++)
		{
			cubes[i].update();
		}
		
        System::paint();
        ts.next();
    }
    
    //AudioTracker::play(Music);
}
