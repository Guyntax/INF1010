//TODO Entête du fichier

#ifndef FONCTEURS_H
#define FONCTEURS_H

#include <memory>
#include <utility>


// DONE : Foncteur ComparateurSecondElementPaire
// Foncteur prédicat binaire comparant les seconds éléments de paires pour déterminer si elles sont en ordre.
// Le foncteur est une classe générique.
// Le template de classe prend deux paramètres, soit les types T1 et T2 tenus par une paire std::pair<T1, T2>.
// L’opérateur() doit prendre en paramètre deux références constantes vers des paires dont les éléments sont de type T1 et T2.
// Il retourne true si le second élément de la première paire est strictement inférieur au second élément de la deuxième paire, false sinon.
template <typename T1, typename T1 >
class ComparateurSecondElementPaire {
public:
	//ComparateurSecondElementPaire()
	bool operator(pair<T1,T2>& lft, pair<T1, T2>& rht)() {
		if (lft.second < rht.second) {
			return true;
		}
		return false;
	}
private:
};

// DONE : Foncteur ComparateurEstEgalAvecId
// Foncteur prédicat unaire servant à comparer un objet(Patient ou Personnel) avec un id de type string.
// Le foncteur est une classe générique.
// Le template de classe prend un seul paramètre de type T.
// L’opérateur() doit prendre en paramètre un pointeur shared_ptr tenant un élément de type T.Il retourne true si l’objet égale à l’id et false si non.
template <typename T>
class ComparateurEstEgalAvecId{
public:
	ComparateurEstEgalAvecId(std::string id) :id_(id) {}
	bool operator()(shared_ptr<T> personne) {
		return *personne == id;
	}
private:
	std::string id_;
};

// TODO : Foncteur AccumulateurPeriodePersonnel
// Foncteur qui se charge de l'ajout de la période passée par les personnels à l'hôpital à une somme.
// L’opérateur() prend 3  paramètres : 
//      somme de type double 
//      pair de type pair de string et shared_ptr de Personnel
//      Il retourne la somme du paramètre somme et  de l’ancienneté du personnel passé en paramètre.
// Indice : utiliser les fonctions getDateCourante et getDateAdhesion pour calculer l’ancienneté en prenant en compte juste les années.
class AccumulateurPeriodePersonnel{
public:
	AccumulateurPeriodePersonnel(double somme): somme_(somme){}
	double operator()(double somme, std::pair<const std::string, std::shared_ptr<Personnel>> pair) {
		/*
		if (comparerDate(getDateCourante(), pair.second->getDateAdhesion())) {
			return somme_ + getDateCourante() - pair.second->getDateAdhesion();
		}
		*/
		return 0; // erreur

	}
private:
	double somme_;
};


// DONE : Foncteur ComparateurTypePatient
// Foncteur prédicat unaire servant à comparer un objet de type Patient à n’importe quel autre objet.
// Le foncteur est une classe générique.
// Le template de classe prend un seul paramètre de type T.
// L’opérateur() doit prendre en paramètre un pointeur shared_ptr tenant un élément de type Patient
// Il retourne true si l’objet est de type Patient et false si non. Hint : conversion dynamique
template <typename T>
class ComparateurTypePatient {
public:
	bool operator()(std::shared_ptr<Patient> patient){
		if (dynamic_cast<T*>(patient.get())) {
			return true;
		}
		return false;
	}
private:

};

// DONE : EstDansIntervalleDatesConsultation
// Foncteur prédicat unaire servant à déterminer si une consultation est réalisée entre deux dates.
// Constructeur par paramètres initalisant l'intervalle de dates. Il prend deux références constantes vers deux objets de type tm.
// L’opérateur() une référence constante vers un shared_ptr de Consultation.
// Utiliser les deux fonctions définis dans utils.h convertirStringDate pour convertir une date de sting vers tm et comparerDate pour comparer deux dates.
class EstDansIntervalleDatesConsultation {
public:
	EstDansIntervalleDatesConsultation(const tm& debut, const tm& fin) :debut_(debut), fin_(fin) {}
	bool operator()(const std::shared_ptr<Consultation>& consultation) {
		tm dateConsultation  = convertirStringDate(consultation->getDate());

		if (comparerDate(dateConsultation, debut_) && comparerDate(fin_, dateConsultation)) {
			return true;
		}
		return false;
	}
private:
	tm debut_;
	tm fin_;
};
#endif // FONCTEURS_H
