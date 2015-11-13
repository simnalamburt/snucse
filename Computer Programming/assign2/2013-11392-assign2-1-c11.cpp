#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using std::string;


//
// 에러메세지를 출력하고 프로그램 종료
//
[[ noreturn ]]
void panic(const char *msg) {
  using namespace std;

  cerr << "\n\n" << msg << "\n\n";
  exit(1);
}


class Container {
public:
  enum class ContainerType { normal, protect, cold };

  // char 로부터 ContainerType을 얻어내는 함수
  static ContainerType type_from_ch(char input) {
    switch (input) {
      case 'N': return ContainerType::normal;
      case 'P': return ContainerType::protect;
      case 'C': return ContainerType::cold;
      default: panic("Invalid container type character has been given");
    }
  }

  const ContainerType type;
  const size_t size;
  const size_t cost;

private:
  // TODO: Hold items

public:
  Container(char type, size_t size, size_t cost) :
    type { type_from_ch(type) }, size { size }, cost { cost } {}
};


class Item {
public:
  enum class ItemType { normal, flammable, ice };

  static ItemType type_from_ch(char input) {
    switch (input) {
      case 'N': return ItemType::normal;
      case 'F': return ItemType::flammable;
      case 'I': return ItemType::ice;
      default: panic("Invalid item type character has been given");
    }
  }

  const string name;
  const ItemType type;
  const size_t size;

  Item(const string &name, char type, size_t size) :
    name { name }, type { type_from_ch(type) }, size { size } {}
  Item(string &&name, char type, size_t size) :
    name { name }, type { type_from_ch(type) }, size { size } {}
};

namespace {
  using std::ostream;
  using Cty = Container::ContainerType;
  using Ity = Item::ItemType;

  ostream& operator<<(ostream& os, Cty ty) {
    switch (ty) {
      case Cty::normal:  return os << "normal";
      case Cty::protect: return os << "protect";
      case Cty::cold:    return os << "cold";
    }
  }

  ostream& operator<<(ostream& os, Ity ty) {
    switch (ty) {
      case Ity::normal:    return os << "normal";
      case Ity::flammable: return os << "flammable";
      case Ity::ice:       return os << "ice";
    }
  }
}


int main(int argc, char* argv[]) {
  using namespace std;

  if (argc != 3) {
    cerr << "Wrong usage." << endl;
    cerr << endl;
    cerr << "Example:" << endl;
    cerr << "    " << argv[0] << " input.txt output.txt" << endl;
    return 1;
  }
  assert(argc == 3);

  const auto iname = argv[1];
  const auto oname = argv[2];

  vector<Container> containers;
  vector<Item> items;

  {
    auto input = ifstream { iname };
    size_t item_count;
    input >> item_count;

    for (size_t _ = 0; _ < 3; ++_) {
      char type;
      size_t size, cost;
      input >> size >> type >> cost;
      containers.emplace_back(type, size, cost);
    }

    for (size_t _ = 0; _ < item_count; ++_) {
      string name;
      char type;
      size_t size;
      input >> name >> size >> type;
      items.emplace_back(move(name), type, size);
    }
  }

  // TODO
  for (const auto& container: containers) {
    cout << container.type << " = { size: " << container.size << ", cost: " << container.cost << " }\n";
  }
  for (const auto& item: items) {
    cout << item.name << ": " << item.type << " = " << item.size << endl;
  }

  return 0;
}
