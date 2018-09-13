#include "LineRasterizer.h"
#include "Utilities.h"


void DrawLineDDA(float X1, float Y1, float X2, float Y2, float distance1, float distance2, Color rgb)
{
  BOOLEAN SameX = float_IsEqual(X1, X2);
  BOOLEAN SameY = float_IsEqual(Y1, Y2);
  float xMin = 0;
  float xMax = WIDTH;
  float yMin = 0;
  float yMax = HEIGHT;
  
   if(X1 < xMin && X2 < xMin)
  {
    return;
  }
  else if(X1 > xMax && X2 > xMax)
  {
    return;
  }
  if(Y1 < yMin && Y2 < yMin)
  {
    return;
  }
  else if(Y1 > yMax && Y2 > yMax)
  {
    return;
  }
  
  if(!(X1 >= 0) && !(X1 <= 0))
    return;
  else if(!(X2 >= 0) && !(X2 <= 0))
    return;
  else if(!(Y1 >= 0) && !(Y1 <= 0))
    return;
  else if(!(Y2 >= 0) && !(Y2 <= 0))
    return;
  /*
  else if(X1 < xMin || X1 > xMax)
    return;
  else if(X2 < xMin || X2 > xMax)
    return;
  else if(Y1 < yMin || Y1 > yMax)
    return;
  else if(Y2 < yMin || Y2 > yMax)
    return;
    */
  //just one pixel
  else if(SameX && SameY)
  {
    FrameBuffer_SetPixel(&GlobalFrameBuffer, X1, Y1,rgb.Red, rgb.Green, rgb.Blue, distance1);
  }
  else if(SameX) //vertical line
  {
    DrawVerticalLine(X1, Y1, Y2, rgb, distance1, distance2);
  }
  else if(SameY) //horizontal line
  {
    DrawHorizontalLine(X1, X2, Y1, rgb, distance1, distance2);
  }
  else 
  {
    float Slope = (Y2 - Y1)/(X2 - X1);
    float x1 = X1, x2 = X2, y1 = Y1, y2 = Y2;
    float d1 = distance1, d2 = distance2;
    if(x1 < xMin)
    {
      d1 = (d1 - d2) * (xMin - X2) / (X1 - X2) + d2;
      y1 = Slope * (xMin - X1) + Y1;
      x1 = xMin;
    }
    if(x1 > xMax)
    {
      d1 = (d1 - d2) * (xMax - X2) / (X1 - X2) + d2;
      y1 = Slope * (xMax - X1) + Y1;
      x1 = xMax;
    }
    if(x2 < xMin)
    {
      d2 = (d2 - d1) * (xMin - X1) / (X2 - X1) + d1;
      y2 = Slope * (xMin - X1) + Y1;
      x2 = xMin;
    }
    if(x2 > xMax)
    {
      d2 = (d2 - d1) * (xMax - X1) / (X2 - X1) + d1;
      y2 = Slope * (xMax - X1) + Y1;
      x2 = xMax;
    }
    if(y1 < yMin)
    {
      d1 = (d1 - d2) * (yMin - Y2) / (Y1 - Y2) + d2;
      x1 = 1 / Slope * (yMin - Y1) + X1;
      y1 = yMin;
    }
    if(y1 > yMax)
    {
      d1 = (d1 - d2) * (yMax - Y2) / (Y1 - Y2) + d2;
      x1 = 1 / Slope * (yMax - Y1) + X1;
      y1 = yMax;
    }
    if(y2 < yMin)
    {
      d2 = (d2 - d1) * (yMin - Y1) / (Y2 - Y1) + d1;
      x2 = 1 / Slope * (yMin - Y1) + X1;
      y2 = yMin;
    }
    if(y2 > yMax)
    {
      d2 = (d2 - d1) * (yMax - Y1) / (Y2 - Y1) + d1;
      x2 = 1 / Slope * (yMax - Y1) + X1;
      y2 = yMax;
    }
    //slope greater than 1
    if(Slope >= 1.0f || Slope <= -1.0f)
    {
      DrawLineDDALargeSlope(x1, y1, x2, y2, rgb, d1, d2);
    }
    else //slope less than 1
    {
      DrawLineDDASmallSlope(x1, y1, x2, y2, rgb, d1, d2);
    }
  }

}
void DrawVerticalLine(float X, float Y1, float Y2, Color rgb, float distance1, float distance2)
{

  //move to integers (Round)
  int RoundedY1 = Round(Y1);
  int RoundedY2 = Round(Y2);
  int RoundedX = Round(X);
  float distance = distance1;
  float dIncrement = (distance2 - distance1) / (RoundedY2 - RoundedY1);
  //check to see if we are walking up or down the line
  int Increment = RoundedY2 > RoundedY1 ? 1 : -1;
  dIncrement *= Increment;
  // while they aren't the same, set the pixel and move on
  while(RoundedY1 != RoundedY2)
  {
    FrameBuffer_SetPixel(&GlobalFrameBuffer, RoundedX, RoundedY1, rgb.Red, rgb.Green, rgb.Blue, distance);
    RoundedY1 += Increment;
    distance += dIncrement;
  }

  //set the pixel where Y1 == Y2
  FrameBuffer_SetPixel(&GlobalFrameBuffer, RoundedX, RoundedY1,  rgb.Red, rgb.Green, rgb.Blue, distance);

}
void DrawHorizontalLine(float X1, float X2, float Y, Color rgb, float distance1, float distance2)
{
    //move to integers (Round)
  int RoundedX1 = Round(X1);
  int RoundedX2 = Round(X2);
  int RoundedY = Round(Y);
  float distance = distance1;
  float dIncrement = (distance2 - distance1) / (RoundedX2 - RoundedX1);
  //check to see if we are walking up or down the line
  int Increment = RoundedX2 > RoundedX1 ? 1 : -1;
  dIncrement *= Increment;
  // while they aren't the same, set the pixel and move on
  while(RoundedX1 != RoundedX2)
  {
    FrameBuffer_SetPixel(&GlobalFrameBuffer, RoundedX1 ,RoundedY,  rgb.Red, rgb.Green, rgb.Blue, distance);
    RoundedX1 += Increment;
    distance += dIncrement;
  }

  //set the pixel where Y1 == Y2
  FrameBuffer_SetPixel(&GlobalFrameBuffer, RoundedX1, RoundedY,  rgb.Red, rgb.Green, rgb.Blue, distance);
}
void DrawLineDDALargeSlope(float X1, float Y1, float X2, float Y2, Color rgb, float distance1, float distance2)
{
   //Y2 - Y1 = 0, should be taken care of in earlier case
  float invslope = (X2 - X1)/(Y2 - Y1);
  
  //will iterate through X, calculating Y
  int YStart = Round(Y1);
  int YEnd = Round (Y2);
  int YIncrement = Y1 < Y2 ? 1 : -1;
  float XIncrement = X1;
  float distance = distance1;
  float dIncrement = (distance2 - distance1) / (YEnd - YStart);
  dIncrement *= YIncrement;
  while(YStart != YEnd)
  {
    FrameBuffer_SetPixel(&GlobalFrameBuffer, Round(XIncrement), YStart,  rgb.Red, rgb.Green, rgb.Blue, distance);
    YStart += YIncrement; //either 1 or -1
    XIncrement += invslope * YIncrement; //calculate the next y
    distance += dIncrement;
  }
  //Y increment should be Y2 at this point
  FrameBuffer_SetPixel(&GlobalFrameBuffer, Round(XIncrement), YStart,  rgb.Red, rgb.Green, rgb.Blue, distance);
  
}
void DrawLineDDASmallSlope(float X1, float Y1, float X2, float Y2, Color rgb, float distance1, float distance2)
{
  //X2 - X1 = 0, should be taken care of in earlier case
  float slope = (Y2 - Y1)/(X2 - X1);
  
  //will iterate through X, calculating Y
  int XStart = Round(X1);
  int XEnd = Round (X2);
  int XIncrement = X1 < X2 ? 1 : -1;
  float YIncrement = Y1;
  float distance = distance1;
  float dIncrement = (distance2 - distance1) / (XEnd - XStart);
  dIncrement *= XIncrement;
  while(XStart != XEnd)
  {
    FrameBuffer_SetPixel(&GlobalFrameBuffer, XStart, Round(YIncrement), rgb.Red, rgb.Green, rgb.Blue, distance);
    XStart += XIncrement; //either 1 or -1
    YIncrement += slope * XIncrement; //calculate the next y
    distance += dIncrement;
  }
  //Y increment should be Y2 at this point
  FrameBuffer_SetPixel(&GlobalFrameBuffer, XStart, Round(YIncrement),  rgb.Red, rgb.Green, rgb.Blue, distance);
  

}

void DrawFilledTriangle(float fX1, float fY1, float fX2, float fY2, float fX3, float fY3, float distance1, float distance2, float distance3, Color rgb)
{
  float X1 = Round(fX1), X2 = Round(fX2), X3 = Round(fX3);
  float Y1 = Round(fY1), Y2 = Round(fY2), Y3 = Round(fY3);
  int highPointId = 0, middlePointId = 0, lowPointId = 0;
  float y;
  int increment = 1;
  float highPointX = 0.0f, highPointY = 0.0f, middlePointX = 0.0f, middlePointY = 0.0f, lowPointX = 0.0f, lowPointY = 0.0f;
  float m, m2;

  float sideDistance1, sideDistance2; /*side distances are the distances of the edges of the triangles at certain points*/
  float highDistance, middleDistance, lowDistance;

  DrawUnfilledTriangle(X1, Y1, X2, Y2, X3, Y3, distance1, distance2, distance3, rgb);
  if( Y1 == Y2 && Y2 == Y3 )
  {
    DrawLineDDA(X1, Y1, X2, Y1, distance1, distance2, rgb);
    DrawLineDDA(X2, Y1, X3, Y1, distance2, distance3, rgb);
  }
  else if(X1 == X2 && X2 == X3)
  {
    DrawLineDDA(X1, Y1, X1, Y2, distance1, distance2, rgb);
    DrawLineDDA(X1, Y2, X1, Y3, distance2, distance3, rgb);
  }
  else if(Y1 == Y2 || Y2 == Y3 || Y3 == Y1)
  {
    if(Y1 == Y2)
    {
      y = Y3;
      if(Round(Y3) > Round(Y1))
      {
        increment = -1;
      }
      if(Round(X1 - X3) == 0)
      {
        m = 999999; /*division by zero is bad, give something close*/
      }
      else if(Round(Y1 - Y3) == 0)
      {
        m = 0.00001f;
      }
      else
      {
        m = (Y1 - Y3) / (X1 - X3);
      }
      if(Round(X2 - X3) == 0)
      {
        m2 = 999999;
      }
      else if(Round(Y2 - Y3) == 0)
      {
        m2 = 0.00001f;
      }
      else
      {
        m2 = (Y2 - Y3) / (X2 - X3);
      }
      while(Round(y) != Round(Y1))
      {
        y += increment;
        sideDistance1 = (distance1 - distance3) * (y - Y3)/(Y1 - Y3) + distance3;/*Y3 to Y1*/
        sideDistance2 = (distance2 - distance3) * (y - Y3)/(Y2 - Y3) + distance3;/*Y3 to Y2*/
        DrawLineDDA((Y3 - y) / -m + X3, y, (Y3 - y) / -m2 + X3, y, sideDistance1, sideDistance2, rgb);
      }
    }
    else if(Y2 == Y3)
    {
      y = Y1;
      if(Round(Y1) > Round(Y2))
      {
        increment = -1;
      }
      if(Round(X2 - X1) == 0)
      {
        m = 999999; /*division by zero is bad, give something close*/
      }
      else if(Round(Y2 - Y1) == 0)
      {
        m = 0.00001f;
      }
      else
      {
        m = (Y2 - Y1) / (X2 - X1);
      }
      if(Round(X3 - X1) == 0)
      {
        m2 = 999999;
      }
      else if(Round(Y3 - Y1) == 0)
      {
        m2 = 0.00001f;
      }
      else
      {
        m2 = (Y3 - Y1) / (X3 - X1);
      }
      while(Round(y) != Round(Y2))
      {
        y += increment;
        sideDistance1 = (distance2 - distance1) * (y - Y1)/(Y2 - Y1) + distance1;/*Y1 to Y2*/
        sideDistance2 = (distance3 - distance1) * (y - Y1)/(Y3 - Y1) + distance1;/*Y1 to Y3*/
        DrawLineDDA((Y1 - y) / -m + X1, y, (Y1 - y) / -m2 + X1, y, sideDistance1, sideDistance2, rgb);
      }
    }
    else if(Y1 == Y3)
    {
      y = Y2;
      if(Round(Y2) > Round(Y3))
      {
        increment = -1;
      }
      if(Round(X3 - X2) == 0)
      {
        m = 999999; /*division by zero is bad, give something close*/
      }
      else if(Round(Y3 - Y2) == 0)
      {
        m = 0.00001f;
      }
      else
      {
        m = (Y3 - Y2) / (X3 - X2);
      }
      if(Round(X1 - X2) == 0)
      {
        m2 = 999999;
      }
      else if(Round(Y1 - Y2) == 0)
      {
        m2 = 0.00001f;
      }
      else
      {
        m2 = (Y1 - Y2) / (X1 - X2);
      }
      while(Round(y) != Round(Y3))
      {
        y += increment;
        sideDistance1 = (distance3 - distance2) * (y - Y2)/(Y3 - Y2) + distance2;/*Y2 to Y3*/
        sideDistance2 = (distance1 - distance2) * (y - Y2)/(Y1 - Y2) + distance2;/*Y2 to Y1*/
        DrawLineDDA((Y2 - y) / -m + X2, y, (Y2 - y) / -m2 + X2, y, sideDistance1, sideDistance2, rgb);
      }
    }
  }
  else
  {
    if(Y1 >= Y2 && Y1 >= Y3)
    {
      highPointId = 1;
    }
    else if(Y2 >= Y3 && Y2 >= Y1)
    {
      highPointId = 2;
    }
    else if(Y3 >= Y1 && Y3 >= Y2)
    {
      highPointId = 3;
    }

    if((Y2 - Y1) * (Y3 - Y1) <= 0)
    {
      middlePointId = 1;
    }
    else if((Y3 - Y2) * (Y1 - Y2) <= 0)
    {
      middlePointId = 2;
    }
    else if((Y2 - Y3) * (Y1 - Y3) <= 0)
    {
      middlePointId = 3;
    }

    if(Y1 < Y2 && Y1 < Y3)
    {
      lowPointId = 1;
    }
    else if(Y2 < Y3 && Y2 < Y1)
    {
      lowPointId = 2;
    }
    else if(Y3 < Y1 && Y3 < Y2)
    {
      lowPointId = 3;
    }

    if(highPointId == 1)
    {
      highPointX = X1;
      highPointY = Y1;
      highDistance = distance1;
    }
    else if(highPointId == 2)
    {
      highPointX = X2;
      highPointY = Y2;
      highDistance = distance2;
    }
    else if(highPointId == 3)
    {
      highPointX = X3;
      highPointY = Y3;
      highDistance = distance3;
    }

    if(middlePointId == 1)
    {
      middlePointX = X1;
      middlePointY = Y1;
      middleDistance = distance1;
    }
    else if(middlePointId == 2)
    {
      middlePointX = X2;
      middlePointY = Y2;
      middleDistance = distance2;
    }
    else if(middlePointId == 3)
    {
      middlePointX = X3;
      middlePointY = Y3;
      middleDistance = distance3;
    }

    if(lowPointId == 1)
    {
      lowPointX = X1;
      lowPointY = Y1;
      lowDistance = distance1;
    }
    else if(lowPointId == 2)
    {
      lowPointX = X2;
      lowPointY = Y2;
      lowDistance = distance2;
    }
    else if(lowPointId == 3)
    {
      lowPointX = X3;
      lowPointY = Y3;
      lowDistance = distance3;
    }

    if(Round(lowPointX - highPointX) == 0)
    {
      m = 99999; /*division by zero is bad, give something close*/
    }
    else if(Round(lowPointY - highPointY) == 0)
    {
      m = 0.00001f;
    }
    else
    {
      m = (lowPointY - highPointY) / (lowPointX - highPointX);
    }
    sideDistance1 = (lowDistance - highDistance) * (middlePointY - highPointY)/(lowPointY - highPointY) + highDistance; /*middle point*/
    DrawFilledTriangle(highPointX, highPointY, middlePointX, middlePointY, (highPointY - middlePointY) / -m + highPointX, middlePointY, highDistance, middleDistance, sideDistance1, rgb);
    DrawFilledTriangle(lowPointX, lowPointY, middlePointX, middlePointY, (highPointY - middlePointY) / -m + highPointX, middlePointY, lowDistance, middleDistance, sideDistance1, rgb);
  }
}

void DrawUnfilledTriangle(float X1, float Y1, float X2, float Y2, float X3, float Y3, float distance1, float distance2, float distance3, Color rgb)
{
  DrawLineDDA(X1, Y1, X2, Y2, distance1, distance2, rgb);
  DrawLineDDA(X2, Y2, X3, Y3, distance2, distance3, rgb);
  DrawLineDDA(X3, Y3, X1, Y1, distance3, distance1, rgb);
}