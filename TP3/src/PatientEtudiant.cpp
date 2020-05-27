// TODO : Entête du fichier
#include "PatientEtudiant.h"
#include <iostream>
#include <string>

//TODO : Constructeur par paramètre pour intialiser tous les attributs. Utiliser la liste d'initialisation
//Il utilise le constructeur de la classe Etudiant et la classe Patient
PatientEtudiant::PatientEtudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie, const std::string& matricule, const std::string& etablissement):
	Patient( nom, dateDeNaissance, numeroAssuranceMaladie),
	Etudiant(nom, dateDeNaissance, matricule, etablissement)
{};


//TODO : surcharge de la méthode afficher
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


//TODO : les getters et les setters si nécessaire
double PatientEtudiant::getTauxRabais() const { return tauxRabais_; };



