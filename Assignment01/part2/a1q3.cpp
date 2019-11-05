#include "pixmap.h"

//this recursive bool function takes 4 arguments, an (PixMap)image to edit, new (Pixel)colour and the starting (int)coordinates
//the function changes the color of all the pixels with same color as the pixel at the starting coordinates within the 
//boundaries created by different colours in the image.
//returns false if the coordinates provided don't fall within the boundary of the image.
bool fill(PixMap& image, const Pixel& fillColour, int x, int y) {

	//initialize a new temp pixel as a copy of the Pixel passed to the function
	//to preserve the color info before changing it.
	Pixel temp;
	temp = image.getPixel(x, y);
	
	//update pixel colour at x,y in the image
	image.setPixel(fillColour, x, y);
	
	int height = image.height();	//height of image in pixels.
	int width = image.width();	//width of image in pixels

	
	if (x >= 0 && y >= 0) {				//ensuring that the provided coordinates
		if (x < width && y < height) {		//fall within the image boundaries
			if ( x < width - 1 && temp == image.getPixel(x + 1, y)) {	//checking if there's a pixel to the right of the current pixel and
				fill(image, fillColour, x + 1, y);			//has the same colour as the original colour of the pixel at x,y
			}
			if ( y > 0 && temp == image.getPixel(x, y - 1)) {		//validating the pixel below the current pixel
				fill(image, fillColour, x, y - 1);
			}
			if ( y < height - 1 && temp == image.getPixel(x, y + 1)) {	//validating pixel above the current pixel
				fill(image, fillColour, x, y + 1);
			}
			if ( x > 0 && temp == image.getPixel(x - 1, y)) {		//validating pixel to the left of the current pixel
				fill(image, fillColour, x - 1, y);
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

	return true;
}
