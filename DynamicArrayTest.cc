#include <DynamicArray/DynamicArray.h>

#include <string>
#include <vector>
#include <iostream>

int main(void) {
  std::cout << "Dynamic array!" << std::endl;

  DynamicArray<std::string> names;
  std::string name = "Jeffy"; 

  //Move
  DynamicArray<std::string>::ValueHandle jarnathan_ref = names.EmplaceBack("Jarnathan!");
  std::get<std::string&>(jarnathan_ref) = "JARNATHAN NOOOO!";

  names.PushBack("Jolkivic"); 

  names.PopBack();

  names.EmplaceBack("The Great One");

  //names.PushBack(name); Uncomment line and jarnathan_ref will become invalidated because container
  //has resized, and thus memory was moved

  if (names.IsValueHandleValid(jarnathan_ref)) {
    std::cout << "Handle is valid: \n";
    std::cout << std::get<std::string&>(jarnathan_ref) << std::endl;
  }
 
  std::cout << "Names capacity: " << names.GetCapacity() << std::endl;
  for (int i = 0; i < names.GetSize(); ++i) {
    std::cout << names[i] << "\n";
  }

  DynamicArray<int> numbers;

  for (int i = 0; i < 1000; ++i) {
    numbers.PushBack(i * 7);
    if (i % 2 == 0) {
      numbers.PopBack();
    }
  }

  for (int i = 0; i < numbers.GetSize(); ++i) {
    int index = i + i + 1; //Index if we didn't pop back every even number.
    std::cout << index << ": " << numbers[i] << "\n";
  }

  
 

  return 0;
}