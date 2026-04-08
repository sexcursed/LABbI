#include "name.h"
#include "person.h"
#include "city.h"
#include "cat.h"
#include <iostream>

int main(){

  Name name_1;
  name_1.set_first_name("Kleopatra");
  Name name_2("Pushkin", "Alexander", "Sergeevich");
  Name name_3("Mayakovskii", "Vladimir");
  std::cout << "\nTask 1.3:\n\n";

  name_1.print();
  name_2.print();
  name_3.print();


  std::cout << "--------------------\nTask 2.2:\n\n";

  std::shared_ptr<Person> kleo = std::make_shared<Person>(name_1, 152);
  std::shared_ptr<Person> pushkin = std::make_shared<Person>(name_2, 167);
  std::shared_ptr<Person> mayak = std::make_shared<Person>(name_3, 189);

  kleo->print();
  pushkin->print();
  mayak->print();


  std::cout << "--------------------\nTask 2.3:\n\n";
  
  
  std::shared_ptr<Person> ivan = std::make_shared<Person>(Name("Chudov", "Ivan"),167);
  std::shared_ptr<Person> petr = std::make_shared<Person>(Name("Chudov", "Petr"),165,ivan);
  std::shared_ptr<Person> boris = std::make_shared<Person>(Name("","Boris"),166,petr);

  ivan->print();
  petr->print();
  boris->print();


  std::cout << "--------------------\nTask 3.3:\n\n";


  City a("A"), b("B"), c("C"), d("D"), e("E"), f("F");
  a.add_path(&b,5);
  a.add_path(&f,1);
  a.add_path(&d,6);
  b.add_path(&a,5);
  b.add_path(&c,3);
  c.add_path(&b,3);
  c.add_path(&d,4);
  d.add_path(&c,4);
  d.add_path(&e,2);
  d.add_path(&a,6);
  e.add_path(&f,2);
  f.add_path(&e,2);
  f.add_path(&b,1);
  a.print();
  b.print();
  c.print();
  d.print();
  e.print();
  f.print();


  std::cout << "--------------------\nTask 4.6:\n\n";


  std::shared_ptr<Person> lev = std::make_shared<Person>("Lev", 170);
  std::shared_ptr<Person> sergey = std::make_shared<Person>(Name("Pushkin", "Sergey"), 168, lev);
  std::shared_ptr<Person> alex = std::make_shared<Person>("Alexander", 167, sergey);

  lev->print();
  sergey->print();
  alex->print();


  std::cout << "--------------------\nTask 5.2:\n\n";


  Cat cat("Barsik");
  cat.meow();
  cat.meow(3);
  return 0;
}