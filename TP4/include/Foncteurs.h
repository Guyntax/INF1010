//! Implémentations des foncteurs
//! \authors Didier Blach-Lafleche & Maude Tremblay
//! \date 14 juin 2020

#ifndef FONCTEURS_H
#define FONCTEURS_H

#include <memory>
#include <utility>
#include "utils.h"
#include <Personnel.h>
#include <Patient.h>
#include <Consultation.h>


// DONE : Foncteur ComparateurSecondElementPaire
// Foncteur pr�dicat binaire comparant les seconds �l�ments de paires pour d�terminer si elles sont en ordre.
// Le foncteur est une classe g�n�rique.
// Le template de classe prend deux param�tres, soit les types T1 et T2 tenus par une paire std::pair<T1, T2>.
// L�op�rateur() doit prendre en param�tre deux r�f�rences constantes vers des paires dont les �l�ments sont de type T1 et T2.
// Il retourne true si le second �l�ment de la premi�re paire est strictement inf�rieur au second �l�ment de la deuxi�me paire, false sinon.
template <typename T1, typename T2 >
class ComparateurSecondElementPaire {
public:
	//ComparateurSecondElementPaire()
	bool operator()(const std::pair<T1,T2>& lft,const std::pair<T1, T2>& rht) {
		return *(lft.second) < *(rht.second);
	}
};

// DONE : Foncteur ComparateurEstEgalAvecId
// Foncteur pr�dicat unaire servant � comparer un objet(Patient ou Personnel) avec un id de type string.
// Le foncteur est une classe g�n�rique.
// Le template de classe prend un seul param�tre de type T.
// L�op�rateur() doit prendre en param�tre un pointeur shared_ptr tenant un �l�ment de type T.Il retourne true si l�objet �gale � l�id et false si non.
template <typename T>
class ComparateurEstEgalAvecId{
public:
	ComparateurEstEgalAvecId(std::string id) :id_(id) {}
	bool operator()(std::shared_ptr<T> personne) {
		return *personne == id_;
	}
private:
	std::string id_;
};

// DONE : Foncteur AccumulateurPeriodePersonnel
// Foncteur qui se charge de l'ajout de la p�riode pass�e par les personnels � l'h�pital � une somme.
// L�op�rateur() prend 3  param�tres : 
//      somme de type double 
//      pair de type pair de string et shared_ptr de Personnel
//      Il retourne la somme du param�tre somme et  de l�anciennet� du personnel pass� en param�tre.
// Indice : utiliser les fonctions getDateCourante et getDateAdhesion pour calculer l�anciennet� en prenant en compte juste les ann�es.
class AccumulateurPeriodePersonnel{
public:
	AccumulateurPeriodePersonnel(double somme): somme_(somme){}
	double operator()(double somme, std::pair<const std::string, std::shared_ptr<Personnel>> pair) {
		somme_ = somme;
		tm TM1 = getDateCourante();
		tm TM2 = pair.second->getDateAdhesion();
		
		if (comparerDate(TM1, TM2 )) {
			return somme_ + getDateCourante().tm_year - pair.second->getDateAdhesion().tm_year;
		}
		return 0; // si erreur

	}
private:
	double somme_;
};


// DONE : Foncteur ComparateurTypePatient
// Foncteur pr�dicat unaire servant � comparer un objet de type Patient � n�importe quel autre objet.
// Le foncteur est une classe g�n�rique.
// Le template de classe prend un seul param�tre de type T.
// L�op�rateur() doit prendre en param�tre un pointeur shared_ptr tenant un �l�ment de type Patient
// Il retourne true si l�objet est de type Patient et false si non. Hint : conversion dynamique
template <typename T>
class ComparateurTypePatient {
public:
	bool operator()(std::shared_ptr<Patient> patient){
		return  (dynamic_cast<T*>(patient.get()));
	}
};

// DONE : EstDansIntervalleDatesConsultation
// Foncteur pr�dicat unaire servant � d�terminer si une consultation est r�alis�e entre deux dates.
// Constructeur par param�tres initalisant l'intervalle de dates. Il prend deux r�f�rences constantes vers deux objets de type tm.
// L�op�rateur() une r�f�rence constante vers un shared_ptr de Consultation.
// Utiliser les deux fonctions d�finis dans utils.h convertirStringDate pour convertir une date de sting vers tm et comparerDate pour comparer deux dates.
class EstDansIntervalleDatesConsultation {
public:
	EstDansIntervalleDatesConsultation(const tm& debut, const tm& fin) :debut_(debut), fin_(fin) {}
	bool operator()(const std::shared_ptr<Consultation>& consultation) {
		tm dateConsultation  = convertirStringDate(consultation->getDate());
		return comparerDate(dateConsultation, debut_) && comparerDate(fin_, dateConsultation);
	}
private:
	tm debut_;
	tm fin_;
};
#endif // FONCTEURS_H
