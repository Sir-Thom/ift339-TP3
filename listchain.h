/*
Nom:Thomas Toulouse                     CIP:tout3815
Nom:Canis Christabelle Tchonet Toukam   CIP:tchc0901
*/
/*
 * VOTRE EN-TÊTE ICI!
 * Vous pouvez fournir vos réponses en texte ici.
 */

#ifndef TP3_LISTCHAIN_H
#define TP3_LISTCHAIN_H

#include <cstdio>
#include <iostream>
#include <ostream>

/**
 * Classe pour une structure de données de liste chaînée de listes chaînées.
 */
template <typename TYPE> class listchain {
private:
  // Représente un noeud conteneur d'éléments
  struct Noeud {
    TYPE val;
    Noeud *next;

    Noeud() { next = nullptr; }
  };

  // Représente une chaîne de noeuds.
  struct SuperNoeud {
    Noeud *premier_noeud;
    Noeud *dernier_noeud;

    SuperNoeud *prev;
    SuperNoeud *next;
    size_t nbelem; // nombre d'éléments dans la chaîne du super noeud

    SuperNoeud() {
      premier_noeud = dernier_noeud = nullptr;
      prev = next = nullptr;
      nbelem = 0;
    }
  };

  SuperNoeud *debut; // premier super noeud, ou nullptr si la liste est vide
  SuperNoeud *fin;   // dernier super noeud, ou nullptr si la liste est vide
  size_t max_taille; // nombre d'élément maximum qu'un super noeud peut contenir

public:
  listchain()
      : listchain(10) {
        }; // redirige vers l'autre constructeur avec max_taille = 10

  listchain(size_t max_taille_supernoeud); // construit en spécifiant max_taille

  ~listchain();

  listchain(const listchain &source);

  listchain &operator=(const listchain &source);

  TYPE &operator[](size_t i);

  size_t size() const;

  void push_front(const TYPE &val);
  void push_back(const TYPE &val);
  void pop_front();
  void pop_back();

  //*** J'ai pensé demander le insert_at et le erase_at, mais concentrez-vous
  // sur l'intra à la place
  //*** Vous pouvez quand même réfléchir à comment vous l'auriez implémenté
  // void erase_at(const size_t pos);
  // void insert_at(const size_t pos, const TYPE& val);

  void clear(); // remet la liste vide

  void afficher_contenu(); // Affiche le contenu avec une ligne par
                           // sous-tableau.
};

/*------------------------------------------------------------------------------
IMPLÉMENTATION
------------------------------------------------------------------------------*/

/**
 * Constructeur qui initialise avec une liste vide.
 * tabsize est la taille des sous-tableaux
 */
template <typename TYPE>
listchain<TYPE>::listchain(size_t max_taille_supernoeud) {
  max_taille = max_taille_supernoeud;
  debut = fin = nullptr;
}

/**
 * Destructeur qui désalloue toute la mémoire et nettoie
 */
template <typename TYPE> listchain<TYPE>::~listchain() { clear(); }
/*
 * Supprime tous les éléments et remet à l'état d'une liste vide.
 */
template <typename TYPE> void listchain<TYPE>::clear() {
  while (debut) {
    SuperNoeud *sn = debut;
    debut = debut->next;

    while (sn->premier_noeud) {
      Noeud *n = sn->premier_noeud;
      sn->premier_noeud = n->next;
      delete n;
    }
    delete sn;
  }
  fin = nullptr;
}

/**
 * Constructeur par copie: met la liste à vide et délègue tout à l'opérateur =
 */
template <typename TYPE> listchain<TYPE>::listchain(const listchain &source) {
  while (debut) {
    SuperNoeud *sn = debut;
    debut = debut->next;

    // Supprimer tous les Noeuds de ce SuperNoeud
    while (sn->premier_noeud) {
      Noeud *n = sn->premier_noeud;
      sn->premier_noeud = n->next;
      delete n;
    }

    delete sn;
  }
  fin = nullptr;
}

/**
 * Opérateur =
 * Nettoie l'objet courant et copie tout de la source
 */
template <typename TYPE>
listchain<TYPE> &listchain<TYPE>::operator=(const listchain &src) {
  // NOTE: puisque vous n'avez pas à recopier exactement les mêmes super noeuds
  // Il faut juste que le contenu soit le même, mais pas nécessairement les
  // nbelem des super noeuds. Ceci devrait vous simplifier la tâche.
  if (this != &src) {
    clear();
  }
  SuperNoeud *current = src.debut;
  while (current) {
    push_back(current->premier_noeud->val);
    current = current->next;
  }
  return *this;
}

/**
 * Retourne le i-ème élément.
 */
template <typename TYPE> TYPE &listchain<TYPE>::operator[](size_t i) {
  // aucune vérification de borne à faire
  SuperNoeud *current = debut;
  while (current && i >= current->nbelem) {
    i -= current->nbelem;
    current = current->next;
  }
  Noeud *node = current->premier_noeud;

  while (i--) {
    node = node->next;
  }
  return node->val;
}

/**
 * Retourne le nombre d'éléments dans votre liste.
 */
template <typename TYPE> size_t listchain<TYPE>::size() const {
  size_t total_size = 0;
  SuperNoeud *current = debut;

  while (current) {
    total_size += current->nbelem;
    current = current->next;
  }
  return total_size;
}

/**
 * Ajouter en début de liste.  Insérer une nouvelle cellule au début si
 * nécessaire.
 */
template <typename TYPE> void listchain<TYPE>::push_front(const TYPE &val) {
  // N'oubliez pas de maintenir les nbelem ( je le dis car j'oubliais toujours
  // :P )
  Noeud *new_node = new Noeud();
  new_node->val = val;

  if (!debut) {
    SuperNoeud *new_super_node = new SuperNoeud();

    new_super_node->premier_noeud = new_node;
    new_super_node->dernier_noeud = new_node;
    new_super_node->nbelem = 1;
    debut = fin = new_super_node;
  } else {
    if (debut->nbelem < max_taille) {
      new_node->next = debut->premier_noeud;
      debut->premier_noeud = new_node;
      debut->nbelem++;
    } else {
      SuperNoeud *new_super_node = new SuperNoeud();
      new_super_node->premier_noeud = new_node;
      new_super_node->dernier_noeud = new_node;
      new_super_node->nbelem = 1;

      new_super_node->next = debut;
      debut->prev = new_super_node;
      debut = new_super_node;
    }
  }
}

/**
 * Ajouter en fin de liste.  Ajouter une nouvelle cellule à la fin si
 * nécessaire.
 */
template <typename TYPE> void listchain<TYPE>::push_back(const TYPE &val) {
  Noeud *new_node = new Noeud();
  new_node->val = val;

  if (!fin) {
    SuperNoeud *new_super_node = new SuperNoeud();

    new_super_node->premier_noeud = new_node;
    new_super_node->dernier_noeud = new_node;
    new_super_node->nbelem = 1;
    debut = fin = new_super_node;
  } else {
    if (fin->nbelem < max_taille) {
      fin->dernier_noeud->next = new_node;
      fin->dernier_noeud = new_node;
      fin->nbelem++;
    } else {
      SuperNoeud *new_super_node = new SuperNoeud();
      new_super_node->premier_noeud = new_node;
      new_super_node->dernier_noeud = new_node;
      new_super_node->nbelem = 1;

      fin->next = new_super_node;
      new_super_node->prev = fin;
      fin = new_super_node;
    }
  }
}

/**
 * Enlève l'élément en tête de liste.  Ne vérifie rien.
 */
template <typename TYPE> void listchain<TYPE>::pop_front() {
  if (!debut)
    return;

  // cas 1 retire le premier élément. Si le premier super noeud devient vide et
  // enlever le supernoeud
  if (debut->nbelem == 1) {
    delete debut->dernier_noeud;
    SuperNoeud *debut_next_supernode = debut->next;
    delete debut;
    debut = debut_next_supernode;

    if (!debut)
      fin = nullptr;
    else
      debut->prev = nullptr;
  } else { // cas 2 supprime elt dans le super noeud
    Noeud *prevNode = debut->premier_noeud;
    debut->premier_noeud = debut->premier_noeud->next;
    if (prevNode) {
      delete prevNode;
    }
    debut->nbelem--;
  }
}

/**
 * Enlève l'élément en fin de liste.  Ne vérifie rien.
 */
template <typename TYPE> void listchain<TYPE>::pop_back() {
  // je le fais pour vous

  if (!fin) // liste vide
    return;

  // cas 1: le dernier super noeud a un seul element -> il va disparaître
  if (fin->nbelem == 1) {
    delete fin->premier_noeud; // le premier est aussi le dernier

    SuperNoeud *finprev = fin->prev;
    delete fin;
    fin = finprev;

    if (!finprev) // si on vient de supprimer le dernier super noeud
      debut = nullptr;
    else
      fin->next = nullptr;
  }
  // cas 2: on doit supprimer le dernier elt de fin.
  // On est obligé de boucler pour aller chercher l'avant-dernier noeud de la
  // sous-liste.
  else {
    Noeud *v_prev = fin->premier_noeud;
    Noeud *v = fin->premier_noeud->next;

    while (v->next) {
      v_prev = v;
      v = v->next;
    }
    delete v;
    v_prev->next = nullptr;

    fin->dernier_noeud = v_prev;

    fin->nbelem--;
  }
}
/**
 * Affiche le contenu avec une ligne par sous-tableau.  Un X veut dire "case
 * non-utilisée"
 */
template <typename TYPE> void listchain<TYPE>::afficher_contenu() {
  std::cout << "-------------------------------------" << std::endl;
  std::cout << "size() = " << size() << std::endl;

  SuperNoeud *sn = debut;
  while (sn) {

    std::cout << "[" << sn->nbelem << "] ";
    Noeud *v = sn->premier_noeud;
    while (v) {
      std::cout << v->val << " ";
      v = v->next;
    }
    std::cout << std::endl;

    sn = sn->next;
  }
}

#endif // TP3_LISTCHAIN_H
