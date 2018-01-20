#include <iostream>

// Shapes

class Shape {
  public:
    virtual void draw() = 0;
};

class Square : public Shape {
  public:
    void draw() {
      std::cout << "square";
    }
};

class Rectangle : public Shape {
  public:
    void draw() {
      std::cout << "rectangle";
    }
};

class Circle : public Shape {
  public:
    void draw() {
      std::cout << "circle";
    }
};

class Ellipse : public Shape {
  public:
    void draw() {
      std::cout << "ellipse";
    }
};

// Factories

class ShapeFactory {
  public:
    virtual Shape* createCurvedInstance() = 0;
    virtual Shape* createStraightInstance() = 0;
};

class SimpleShapeFactory : public ShapeFactory {
  public:
    Shape* createCurvedInstance() {
      return new Circle;
    }

    Shape* createStraightInstance() {
      return new Square;
    }
};

class RobustShapeFactory : public ShapeFactory {
  public:
    Shape* createCurvedInstance() {
      return new Ellipse;
    }

    Shape* createStraightInstance() {
      return new Rectangle;
    }
};

int main(int argc, char *argv[]) {
  ShapeFactory* factories[] = {
    new SimpleShapeFactory,
    new RobustShapeFactory
  };

  Shape* shapes[4];

  for(int i = 0; i < 2; i++) {
    shapes[i * 2] = factories[i]->createStraightInstance();
    shapes[i * 2 + 1] = factories[i]->createCurvedInstance();
  }

  for(int i = 0; i < 4; i++) {
    shapes[i]->draw();
    std::cout << std::endl;
  }

  return 0;
}
