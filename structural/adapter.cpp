#include <iostream>

// Rectangle interface
class Rectangle {
  public:
    virtual void draw() = 0;
};

class LegacyRectangle {
  int x1, x2, y1, y2;

  public:
    LegacyRectangle(int x1, int x2, int y1, int y2) {
      this->x1 = x1;
      this->x2 = x2;
      this->y1 = y1;
      this->y2 = y2;
    }

    void oldDraw() {
      std::cout << "Old draw: "
        << x1 << ',' << x2 << ','
        << y1 << ',' << y2 << std::endl;
    }
};

class RectangleAdapter : public Rectangle, private LegacyRectangle {
  int x, y, width, height;

  public:
    RectangleAdapter(int x, int y, int w, int h) :
      LegacyRectangle(x, x + w, y, y + h) {
        this->x = x;
        this->y = y;
        this->width = w;
        this->height = h;
    }

    void draw() {
      std::cout << "Draw: "
        << "(" << x << ", " << y << ") "
        << "w: " << width << ", h: " << height
        << std::endl;
      oldDraw();
    }
};

int main(int argc, char* argv[]) {
  Rectangle* rect = new RectangleAdapter(0, 1, 10, 10);
  rect->draw();

  return 0;
}
