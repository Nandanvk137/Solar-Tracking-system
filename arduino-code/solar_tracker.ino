#include <Servo.h>

Servo horizontal;
Servo vertical;

int ldrTopLeft = A0;
int ldrTopRight = A1;
int ldrBottomLeft = A2;
int ldrBottomRight = A3;

int horizontalPos = 90;
int verticalPos = 90;

void setup() {
  horizontal.attach(9);
  vertical.attach(10);

  horizontal.write(horizontalPos);
  vertical.write(verticalPos);

  delay(1000);
}

void loop() {

  int topLeft = analogRead(ldrTopLeft);
  int topRight = analogRead(ldrTopRight);
  int bottomLeft = analogRead(ldrBottomLeft);
  int bottomRight = analogRead(ldrBottomRight);

  int topAvg = (topLeft + topRight) / 2;
  int bottomAvg = (bottomLeft + bottomRight) / 2;
  int leftAvg = (topLeft + bottomLeft) / 2;
  int rightAvg = (topRight + bottomRight) / 2;

  int tolerance = 20;

  // Vertical movement
  if (abs(topAvg - bottomAvg) > tolerance) {
    if (topAvg > bottomAvg) {
      verticalPos--;
    } else {
      verticalPos++;
    }

    verticalPos = constrain(verticalPos, 0, 180);
    vertical.write(verticalPos);
  }

  // Horizontal movement
  if (abs(leftAvg - rightAvg) > tolerance) {
    if (leftAvg > rightAvg) {
      horizontalPos++;
    } else {
      horizontalPos--;
    }

    horizontalPos = constrain(horizontalPos, 0, 180);
    horizontal.write(horizontalPos);
  }

  delay(100);
}
