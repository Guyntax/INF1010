//TODO Ent�te du fichier

#ifndef FONCTEURS_H
#define FONCTEURS_H

#include <memory>
#include <utility>


// TODO : Foncteur ComparateurSecondElementPaire
// Foncteur pr�dicat binaire comparant les seconds �l�ments de paires pour d�terminer si elles sont en ordre.
// Le foncteur est une classe g�n�rique.
// Le template de classe prend deux param�tres, soit les types T1 et T2 tenus par une paire std::pair<T1, T2>.
// L�op�rateur() doit prendre en param�tre deux r�f�rences constantes vers des paires dont les �l�ments sont de type T1 et T2.
// Il retourne true si le second �l�ment de la premi�re paire est strictement inf�rieur au second �l�ment de la deuxi�me paire, false sinon.

// TODO : Foncteur ComparateurEstEgalAvecId
// Foncteur pr�dicat unaire servant � comparer un objet(Patient ou Personnel) avec un id de type string.
// Le foncteur est une classe g�n�rique.
// Le template de classe prend un seul param�tre de type T.
// L�op�rateur() doit prendre en param�tre un pointeur shared_ptr tenant un �l�ment de type T.Il retourne true si l�objet �gale � l�id et false si non.

// TODO : Foncteur AccumulateurPeriodePersonnel
// Foncteur qui se charge de l'ajout de la p�riode pass�e par les personnels � l'h�pital � une somme.
// L�op�rateur() prend 3  param�tres : 
//      somme de type double 
//      pair de type pair de string et shared_ptr de Personnel
//      Il retourne la somme du param�tre somme et  de l�anciennet� du personnel pass� en param�tre.
// Indice : utiliser les fonctions getDateCourante et getDateAdhesion pour calculer l�anciennet� en prenant en compte juste les ann�es.

// TODO : Foncteur ComparateurTypePatient
// Foncteur pr�dicat unaire servant � comparer un objet de type Patient � n�importe quel autre objet.
// Le foncteur est une classe g�n�rique.
// Le template de classe prend un seul param�tre de type T.
// L�op�rateur() doit prendre en param�tre un pointeur shared_ptr tenant un �l�ment de type Patient
// Il retourne true si l�objet est de type Patient et false si non. Hint : conversion dynamique

// TODO : EstDansIntervalleDatesConsultation
// Foncteur pr�dicat unaire servant � d�terminer si une consultation est r�alis�e entre deux dates.
// Constructeur par param�tres initalisant l'intervalle de dates. Il prend deux r�f�rences constantes vers deux objets de type tm.
// L�op�rateur() une r�f�rence constante vers un shared_ptr de Consultation.
// Utiliser les deux fonctions d�finis dans utils.h convertirStringDate pour convertir une date de sting vers tm et comparerDate pour comparer deux dates.

#endif // FONCTEURS_H
