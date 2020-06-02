//! iMPLÉMENTATION de la classe Étudiant. Celle-ci hérite de Patient et de Étudiant.
//! \Authurs: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#include "PatientEtudiant.h"
#include <iostream>
#include <string>

//DONE : Constructeur par paramètre pour intialiser tous les attributs. Utiliser la liste d'initialisation
//Il utilise le constructeur de la classe Etudiant et la classe Patient
PatientEtudiant::PatientEtudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie, const std::string& matricule, const std::string& etablissement):
	Patient( nom, dateDeNaissance, numeroAssuranceMaladie),
	Etudiant(nom, dateDeNaissance, matricule, etablissement),
	tauxRabais_(TAUX_RABAIS)
{};


//DONE : surcharge de la méthode afficher
//Afficher les informations liées au patient
//Puis affichier " | "
//Puis afficher les informations liées à l'étudiant
//Puis afficher " | Taux de rabais: " suivi du tauxRabais_
void PatientEtudiant::afficher(std::ostream& stream)const {
	Patient::afficher(stream);
	stream << " | ";
	Etudiant::afficher(stream);
	stream << " | Taux de rabais: "<< tauxRabais_<< "\n";

};


//DONE : les getters et les setters si nécessaire
double PatientEtudiant::getTauxRabais() const { return tauxRabais_; };



