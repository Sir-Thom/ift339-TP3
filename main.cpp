
#include <iostream>

#include "listchain.h"

// fais une sÃ©rie de push des valeurs min Ã  max.  Si is_back = true, fais des
// push_back, sinon des push_front en ordre inverse de max Ã  min.
void do_multi_push(listchain<int> &liste, int min, int max, bool is_back) {
  if (is_back) {
    for (int i = min; i <= max; ++i)
      liste.push_back(i);
  } else {
    for (int i = max; i >= min; --i) {
      liste.push_front(i);
    }
  }
}

int main() {
  listchain<int> liste(5); // max_taille = 5

  do_multi_push(liste, 1, 18, true);

  liste.afficher_contenu();
  std::cout << "Enumeration des elts: ";
  for (int i = 0; i < liste.size(); ++i) {
    std::cout << liste[i] << " ";
  }
  std::cout << std::endl;

  liste.push_back(19);
  liste.push_back(20);

  liste.afficher_contenu();

  liste.push_back(21);

  liste.afficher_contenu();

  liste.pop_back();
  liste.afficher_contenu();

  liste.pop_back();
  liste.pop_back();
  liste.pop_back();

  liste.afficher_contenu();

  do_multi_push(liste, -15, 0, false);

  liste.afficher_contenu();

  std::cout << "Enumeration des elts: ";
  for (int i = 0; i < liste.size(); ++i) {
    std::cout << liste[i] << " ";
  }
  std::cout << std::endl;

  liste.pop_front();
  liste.afficher_contenu();

  liste.pop_front();
  liste.pop_front();
  liste.pop_front();
  liste.afficher_contenu();

  // test de passage Ã  l'Ã©chelle
  do_multi_push(liste, 1, 1000000, true);
  std::cout << std::endl
            << "Taille apres 1M push: " << liste.size() << std::endl;
}
