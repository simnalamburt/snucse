/*
 * Hello.cpp
 *
 *  Created on: Sep 1, 2015
 *      Author: Yeonil
 */

#include <iostream>
#include <vector>
#include <stdio.h>
//#include "std_lab_facilities.h"

void print(std::vector<int> &v);
void print(int p[], int size);

void lesson1() {
  std::vector<int> first;                              // empty vector of ints
  std::vector<int> second(4, 100);                 // four ints with value 100
  std::cout << "The second of fifth are:";
  print(second);

  std::vector<int> third(second.begin(), second.end()); // iterating through second
  std::cout << "The third of fifth are:";
  print(third);

  std::vector<int> fourth(third);                       // a copy of third
  std::cout << "The fourth of fourth are:";
  print(fourth);

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = { 16, 2, 77, 29 };

  std::cout << "myints : " << myints << std::endl;
  std::cout << "sizeof(myints) / sizeof(int) : "
      << sizeof(myints) / sizeof(int) << std::endl;

  std::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

  std::cout << "The contents of fifth are:";
  print(fifth);
}

void lesson2() {
  int list1[] = { 1, 2, 3, 4, 5, 6, 7 };
  std::cout << "print list1 \n";
  print(list1, 7);

  int list2[3][3];

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      list2[i][j] = i + j;
  std::cout << "print list2 \n";
  for (int i = 0; i < 3; i++)
    print(list2[i], 3);
}

class Lesson3 {
private:
  int* list;
  int list_size;
  int ite;
  void realloc_buckets(int demand_size) {
    int new_size = demand_size;
    if (demand_size < 1) {
      if (list_size == 1)
        return;
      else
        demand_size = 1;
    }

    int* new_bucks = new int[new_size];

    int mlimit = ((new_size < list_size) ? new_size : list_size); //short version of if-else

    for (int i = 0; i < mlimit; i++) {
      new_bucks[i] = list[i];
    }

    delete[] list;
    list = new_bucks;

    list_size = new_size;
  }
public:
  Lesson3() {
    this->list_size = 1;
    this->ite = 0;
    this->list = new int[list_size];
  }
  ~Lesson3() {
    delete[] list;
  }
  void add_item(int hm) {
    if (ite == (list_size - 1)) {
      realloc_buckets(list_size + 1);
    }
    list[ite] = hm;
    ite++;
  }

  void print() {
    for (int i = 0; i < ite; i++)
      std::cout << list[i] << " ";
    std::cout << std::endl;
  }

  bool delete_item(int hm) {
    bool found = false;
    for (int i = 0; i < ite; i++) {
      if (list[i] == hm && !found) {
        found = true;
        list[i] = list[i + 1];
      } else if (found) {
        list[i] = list[i + 1];
      }
    }

    if (found) {
      ite--;
      realloc_buckets(list_size-1);
    }

    return found;
  }
};

void lesson3() {
  Lesson3 item;
  item.add_item(9);
  item.print();
  item.add_item(13);
  item.print();
  item.add_item(9);
  item.print();
  item.add_item(9);
  item.add_item(9);
  item.add_item(9);
  item.print();
  item.delete_item(9);
  item.print();
  item.delete_item(13);
  item.print();
}

int main() {
  //lesson1();
  //lesson2();
  lesson3();
  return 0;
}

void print(std::vector<int> &v) {
  for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void print(int p[], int size) {
  for (int i = 0; i < size; i++)
    std::cout << p[i] << " ";
  std::cout << std::endl;
}
