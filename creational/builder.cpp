#include <iostream>

class Builder {
  protected:

  std::string houseDescription;

  public:

  std::string getHouse() {
    return houseDescription;
  }

  virtual void buildFoundation() = 0;
  virtual void buildWalls() = 0;
  virtual void buildRoof() = 0;
};

class WoodenHouseBuilder : public Builder {
  public:

  void buildFoundation() {
    houseDescription += "There is clay foundation. ";
  }

  void buildWalls() {
    houseDescription += "Wooden walls. ";
  }

  void buildRoof() {
    houseDescription += "Fancy sloping tile roof. ";
  }
};

class StoneHouseBuilder : public Builder {
  public:

  void buildFoundation() {
    houseDescription += "There is concrete with armature foundation. ";
  }

  void buildWalls() {
    houseDescription += "Scary gray stone walls. ";
  }

  void buildRoof() {
    houseDescription += "Metal roof. Full stop. ";
  }
};

class Director {
  std::string buildHouse(Builder* builder) {
    builder->buildFoundation();
    builder->buildWalls();
    builder->buildRoof();
    return builder->getHouse();
  }

  public:

  std::string buildWoodenHouse() {
    return buildHouse(new WoodenHouseBuilder());
  }

  std::string buildStoneHouse() {
    return buildHouse(new StoneHouseBuilder());
  }
};

int main(int argc, char* argv[]) {
  auto director = new Director();
  std::cout << director->buildWoodenHouse() << std::endl;
  std::cout << director->buildStoneHouse() << std::endl;

  return 0;
}
