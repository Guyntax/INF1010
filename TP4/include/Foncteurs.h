//TODO Entête du fichier

#ifndef FONCTEURS_H
#define FONCTEURS_H

#include <memory>
#include <utility>


// TODO : Foncteur ComparateurSecondElementPaire
// Foncteur prédicat binaire comparant les seconds éléments de paires pour déterminer si elles sont en ordre.
// Le foncteur est une classe générique.
// Le template de classe prend deux paramètres, soit les types T1 et T2 tenus par une paire std::pair<T1, T2>.
// L’opérateur() doit prendre en paramètre deux références constantes vers des paires dont les éléments sont de type T1 et T2.
// Il retourne true si le second élément de la première paire est strictement inférieur au second élément de la deuxième paire, false sinon.

// TODO : Foncteur ComparateurEstEgalAvecId
// Foncteur prédicat unaire servant à comparer un objet(Patient ou Personnel) avec un id de type string.
// Le foncteur est une classe générique.
// Le template de classe prend un seul paramètre de type T.
// L’opérateur() doit prendre en paramètre un pointeur shared_ptr tenant un élément de type T.Il retourne true si l’objet égale à l’id et false si non.

// TODO : Foncteur AccumulateurPeriodePersonnel
// Foncteur qui se charge de l'ajout de la période passée par les personnels à l'hôpital à une somme.
// L’opérateur() prend 3  paramètres : 
//      somme de type double 
//      pair de type pair de string et shared_ptr de Personnel
//      Il retourne la somme du paramètre somme et  de l’ancienneté du personnel passé en paramètre.
// Indice : utiliser les fonctions getDateCourante et getDateAdhesion pour calculer l’ancienneté en prenant en compte juste les années.

// TODO : Foncteur ComparateurTypePatient
// Foncteur prédicat unaire servant à comparer un objet de type Patient à n’importe quel autre objet.
// Le foncteur est une classe générique.
// Le template de classe prend un seul paramètre de type T.
// L’opérateur() doit prendre en paramètre un pointeur shared_ptr tenant un élément de type Patient
// Il retourne true si l’objet est de type Patient et false si non. Hint : conversion dynamique

// TODO : EstDansIntervalleDatesConsultation
// Foncteur prédicat unaire servant à déterminer si une consultation est réalisée entre deux dates.
// Constructeur par paramètres initalisant l'intervalle de dates. Il prend deux références constantes vers deux objets de type tm.
// L’opérateur() une référence constante vers un shared_ptr de Consultation.
// Utiliser les deux fonctions définis dans utils.h convertirStringDate pour convertir une date de sting vers tm et comparerDate pour comparer deux dates.

#endif // FONCTEURS_H
