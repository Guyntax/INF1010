//! Implémentation de la classe Étudiantqui représente un patient qui est étudiant. Celle-ci hérite de Patient et de Étudiant.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#include "PatientEtudiant.h"
#include <iostream>
#include <string>

//! Constructeur par paramètre pour intialiser tous les attributs
//! \param nom                    Le nom du patient
//! \param dateDeNaissance        La date de naissance du patient
//! \param numeroAssuranceMaladie Le numero d'assurance maladie du patient
//! \param matricule			matricule de l'étudiant
//! \param établissement		établissement de l'étudiant
PatientEtudiant::PatientEtudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie, const std::string& matricule, const std::string& etablissement):
	Patient( nom, dateDeNaissance, numeroAssuranceMaladie),
	Etudiant(nom, dateDeNaissance, matricule, etablissement),
	tauxRabais_(TAUX_RABAIS)
{};


//! Méthode qui affiche les informations liées au patient
//! \param stream	Le stream dans lequel on affiche les informations
//! \return			stream qui contient les informations du patient etudiant
void PatientEtudiant::afficher(std::ostream& stream)const {
	Patient::afficher(stream);
	stream << " | ";
	Etudiant::afficher(stream);
	stream << " | Taux de rabais: "<< tauxRabais_<< "\n";

	// Le stream est passé par référence, donc pas besoin de le retourner
};


//! Méthode qui retourne le taux de rabais du patient étudiant
//! \return taux de rabais
double PatientEtudiant::getTauxRabais() const { return tauxRabais_; };



