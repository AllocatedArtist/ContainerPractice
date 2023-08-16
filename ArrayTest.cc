#include <Array/Array.h>

#include <iostream>
#include <algorithm>
#include <random>

class Rectangle {
public:
  Rectangle() = default;
  Rectangle(int x, int y, int width, int height) : x_(x), y_(y), width_(width), height_(height) {} 
  int x_ = 0, y_ = 0, width_ = 0, height_ = 0;
};

std::ostream& operator<<(std::ostream& stream, const Rectangle& rect) {
  stream << "[x: " << rect.x_ << ", y: " << rect.y_ 
         << ", width: " << rect.width_ << ", height: " << rect.height_ << "]";

  return stream;
}


int main(void) {
  
  Array<int, 5> numbers{ 3, 4, 6, 10, 12 }; 

  std::cout << "Before change:" << std::endl;
  std::for_each(numbers.begin(), numbers.end(), [](int number) { std::cout << number << "\n"; });

  std::cout << "After change:" << std::endl;

  numbers[0] = 21;
  numbers[1] = 420;
  numbers[4] = 69;

  std::for_each(numbers.begin(), numbers.end(), [](int number) { std::cout << number << "\n"; });


  Array<std::string, 3> names;

  std::cout << "Enter 3 names:" << std::endl;
  for (int i = 0; i < 3; ++i) {
    std::cin >> names[i];
  }

  std::for_each(names.begin(), names.end(), [](const std::string& name) { std::cout << name << "\n"; });

  std::srand(std::time(nullptr));

  Array<Rectangle, 16> rectangles;
  for (size_t x = 0; x < 4; ++x) {
    for (size_t y = 0; y < 4; ++y) {
      int width = std::rand() % 100 + 1;
      int height = std::rand() % 100 + 1;

      //Rectangles array is a w: 4 by h: 4 grid of rectangles.
      rectangles[x + y * 4] = Rectangle(x, y, width, height);
    }
  }

  for (const Rectangle& rect : rectangles) {
    std::cout << rect << "\n";
  }


  return 0;
}