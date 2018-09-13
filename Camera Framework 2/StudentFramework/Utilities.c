#include "Utilities.h"
#include "LineRasterizer.h"
const float FAR_CLIP = 900;
/*const Color backgroundColor = {60, 190, 220};*/
const Color backgroundColor = {180, 240, 255};
DistanceBuffer dBuff;
int Round(f64 input)
{

  int FlooredInput = input;
  
  if(input - FlooredInput > 0.5)
  {
    return FlooredInput + 1;
  }
  else
  {
    return FlooredInput;
  }

}

BOOLEAN float_IsEqual(f32 left, f32 right)
{
  //if difference is within the epsilon range

  return ((left - right) < EPSILON) && 
         ((left - right) > -EPSILON) ? TRUE : FALSE;
}
BOOLEAN double_IsEqual(f64 left, f64 right)
{
   return ((left - right) < EPSILON) && 
          ((left - right) > -EPSILON) ? TRUE : FALSE;
}


//Clears the frame buffer to the given (r, g, b) color
void FrameBuffer_Clear(FrameBuffer * fb,unsigned char r, unsigned char g, unsigned char b)
{
  int i, j;

	for (i=0; i<fb->width; ++i)
	{
		for (j=0; j<fb->height; ++j)
		{
		  fb->buffer[i * 3 + j * fb->width * 3] = r;
			fb->buffer[i * 3 + j * fb->width * 3 + 1] = g;
			fb->buffer[i * 3 + j * fb->width * 3 + 2] = b;
      dBuff.distanceAt[i][j] = FAR_CLIP;
		}
	}
}

void FrameBuffer_ClearToBackground(FrameBuffer* fb)
{
  FrameBuffer_Clear(fb, backgroundColor.Red, backgroundColor.Green, backgroundColor.Blue);
}

//Initializes the frame buffer
void FrameBuffer_Init(FrameBuffer * fb,  unsigned int w, unsigned int h)
{
	fb->width = w;
	fb->height = h;
  fb->buffer = (unsigned char *) malloc(fb->width * fb->height * 3);


	FrameBuffer_Clear(fb, backgroundColor.Red, backgroundColor.Green, backgroundColor.Blue);
}

//Set the pixel's color at (x,y)
void FrameBuffer_SetPixel(FrameBuffer * fb,  int x, int y,  unsigned char r,  unsigned char g,  unsigned char b, float distance)
{
	int _y = fb->height - y;
  float fR = r, fG = g, fB = b;
  unsigned char R = r, G = g, B = b;
  fR = (fR - backgroundColor.Red) * (distance - FAR_CLIP) / -FAR_CLIP + backgroundColor.Red;
  fG = (fG - backgroundColor.Green) * (distance - FAR_CLIP) / -FAR_CLIP + backgroundColor.Green;
  fB = (fB - backgroundColor.Blue) * (distance - FAR_CLIP) / -FAR_CLIP + backgroundColor.Blue;

  R = (unsigned char)fR;
  G = (unsigned char)fG;
  B = (unsigned char)fB;
  if(x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
  {
    if(distance <= dBuff.distanceAt[x][y])
    {
      
	    if (x < 0 || x >= fb->width || _y < 0 || _y >= fb->height)
		    return;

	    fb->buffer[x * 3 + _y * fb->width * 3] = R;
	    fb->buffer[x * 3 + _y * fb->width * 3 + 1] = G;
	    fb->buffer[x * 3 + _y * fb->width * 3 + 2] = B;
      dBuff.distanceAt[x][y] = distance;
    }
  }
}

//Stores the color of the given (x,y) pixel in r, g & b
void FrameBuffer_GetPixel(FrameBuffer * fb, int x,  int y, unsigned char r, unsigned char g, unsigned char b)
{
	int _y = fb->height - y;

	if (x < 0 || x >= fb->width || _y < 0 || _y >= fb->height)
		return;

	r = fb->buffer[x * 3 + _y * fb->width * 3];
	g = fb->buffer[x * 3 + _y * fb->width * 3 + 1];
	b = fb->buffer[x * 3 + _y * fb->width * 3 + 2];
}

void FrameBuffer_Destroy(FrameBuffer * fb)
{
  free(fb->buffer);
}

/////