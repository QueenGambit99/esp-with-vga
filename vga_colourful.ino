#include "fabgl.h"

#include "image.c"

using namespace fabgl;

void setup() {
  struct Primitive prim;
  unsigned int offset = 0;
  unsigned char color  = 0;

  // enable serial
  Serial.begin(115200);  // opens serial port
  while( !Serial ); // for Leonardo

  // print msg to serial output
  delay(500);
  Serial.write("\n\nReset\n");

  // initialize VGA
  VGAController.begin(GPIO_NUM_32, GPIO_NUM_33, /* RED */
                      GPIO_NUM_25, GPIO_NUM_26, /* GREEN */
                      GPIO_NUM_27, GPIO_NUM_14, /* BLUE */
                      GPIO_NUM_17, GPIO_NUM_4); /* SYNC */
  VGAController.setResolution(VGA_640x350_70HzAlt1, 640, 350);

  // loop over pixels
  for(int y = 0; y < 350; y++)
  {
    for(int x = 0; x < 640; x++)
    {
        // get pixel color
        color = bmp_image[offset++];

        // reset VGA pen color
        prim.cmd = SetPenColor;
        prim.color.R = (color>>4)&3;
        prim.color.G = (color>>2)&3;
        prim.color.B = (color>>0)&3;
        VGAController.addPrimitive(prim);

        // draw pixel
        prim.cmd = SetPixel;
        prim.position.X = x;
        prim.position.Y = y;
        VGAController.addPrimitive(prim);
    }
  } 

}

void loop() {

}
