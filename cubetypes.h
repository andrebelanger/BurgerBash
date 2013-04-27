// Burger Bash

#include <sifteo.h>
#include "assets.gen.h"
using namespace Sifteo;


// A representation of our game's cubes. This class CANNOT see the cubes array.
class BurgerBashCube {
public:

	void init(CubeID _cube)
	{
		cube = _cube;
		vid.initMode(BG0_BG1);
		vid.attach(cube);
		
		// Put in the background image
		//int mysteryNumber = ((_cube-1) % 2 == 0 ? 0 : 1);
		imageID = 0;
		vid.bg0.image(vec(0,0), Table, 0);
		
		// Change it to cheese
		/*images[0] = Cheese;
		images[1] = Cheese;
		images[2] = Cheese;
		images[3] = Cheese;
		images[4] = Cheese;*/
	}
	
	void update()
	{
		/*if(cube.accel() > 0)
		{
			LOG("Accelerometer!");
		}*/
	}
	
	// Toggle through images by touch input
	void changeImage()
	{
		// Change image
		if(cube.isTouching())
		{	
			// Check for array out of bounds
			if(imageID < arraysize(images))
			{
				imageID++;
				
				// Loop back to the beginning
				if(imageID == arraysize(images))
				{
					imageID = 0;
				}
			
				// Toggle to the next image
				vid.bg0.image(vec(0,0), images[imageID], 0);
			}
		}
	}
	
	// Change the image to it's neighbor's image
	/*void changeImage(int newID)
	{
		// Update the video buffer
		imageID = newID;
		vid.bg0.image(vec(0,0), images[imageID], 0);
	}*/
	
	// Return imageID, which is private
	int getImageID()
	{
		return imageID;
	}
	
	AssetImage getImage()
	{
		return images[imageID];
	}
	
private:
	CubeID cube;
	VideoBuffer vid;
	int imageID;
	AssetImage images[8] = { Table, BottomBun, Burger, Bacon, Cheese, Ketchup, Lettuce, TopBun };
};


class PlateCube {
public:

	void init(CubeID _cube)
	{
		cube = _cube;
		vid.initMode(BG0_BG1);
		vid.attach(cube);
		
		vid.bg0.image(vec(0,0), Lettuce, 0);
	}
	
	void update()
	{
		
	}
	
	// Change the image to it's neighbor's image
	void changeImage(AssetImage newImage)
	{
		// Update the video buffer
		vid.bg0.image(vec(0,0), newImage, 0);
	}
	
	
	CubeID cube;
	
private:
	VideoBuffer vid;
};