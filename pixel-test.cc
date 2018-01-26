// testing 32 x 16 display pixels

#include "led-matrix.h"
#include "transformer.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>

//using rgb_matrix::GPIO;
//using rgb_matrix::RGBMatrix;
//using rgb_matrix::Canvas;

using namespace rgb_matrix;

static void DrawOnCanvas(Canvas *canvas) {
  /*
   * Really simple animation..
   * Plot pixels one by one. We wait between each step to have a slower animation.
   */

  for (int y = 0; y < 32; y++) {
    for (int x =0; x < 64; x++) {
			// Show where we are on screen. Comment out if using fast animation
			printf("Pixel at (%d, %d)\n", x, y);
      // Draw a pixel at (x, y) where red = 66%, green = 33% and blue = 100% brightness.		
      canvas->SetPixel(x,y , 170, 85, 255); 	
			// Wait a bit... (increase the sleep time if mapping, decrease for testing).
      usleep(1 * 100 * 10);  // 1x100x1000 = 100,000 microseconds or 0.1 seconds.
      // Blank this pixel before drawing the next one if mapping, comment out if filling screen			
//      canvas->SetPixel(x, y, 0, 0, 0); 	
    }
  }

}

int main(int argc, char *argv[]) {
  /*
   * Set up GPIO pins. This fails when not running as root.
   */
  GPIO io;
  if (!io.Init())
    return 1;

  /*
   * Set up the RGBMatrix. It implements a 'Canvas' interface.
   */
  int rows = 16;    // May need to change this to 4, 8, 16 or 32
  int chain = 4;    // Number of boards chained together, may need to double for some panels
  int parallel = 1; // Number of chains in parallel (1..3). > 1 for plus or Pi2

  RGBMatrix *matrix = new RGBMatrix(&io, rows, chain, parallel);

  /*
   * Uncomment this block of code if a transformer is needed or testing a transformer
	 * Don't use a tranformer if trying to discover the panel mapping!
	 */
	 
	/* 
  LinkedTransformer *transformer = new LinkedTransformer();
  matrix->SetTransformer(transformer);
  transformer->AddTransformer(new Snake8x2Transformer());
  */
	
  Canvas *canvas = matrix;

  DrawOnCanvas(canvas);    // Using the canvas.

  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;

	/*
   * Uncomment this block if using a tranformer.
	 */
	 
	/* 
  transformer->DeleteTransformers();
  delete transformer;
  */
	
  return 0;
}
