//! Implémentation de la classe MedecinResident qui représente un médecin résident qui exerce à l’hôpital
//! Cette classe hérite de Personnel et de Étudiant.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020


#include <iostream>
#include <string>
#include "MedecinResident.h"

//!Constructeur par paramètre pour intialiser les attributs de la classe. 
//! \param nom					Nom du médecin résident
//! \param date	de naissance	Date de naissance du médecin résident	
//! \param matricule			matricule du médecin résident
//! \param établissement		établissement du médecin résident
//! \param numeroLicence		id du médecin résident	
//! \param specialite			spécialité du médecin résident
MedecinResident::MedecinResident(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, 
	const std::string& etablissement, const std::string& numeroLicence, Medecin::Specialite specialite):
	Etudiant(nom,dateDeNaissance,matricule,etablissement),
	Medecin(nom,numeroLicence,specialite){}


//! Méthode qui affiche les informations du médecin résident 
//! \param stream	Le stream dans lequel on affiche les informations
//! \return			stream qui contient les informations du médecin résident
void MedecinResident::afficher(std::ostream& stream) const
{
	Medecin::afficher(stream);
	stream << "\n\t";
	Etudiant::afficher(stream);
}

//! Méthode qui retourne le salaire annuel du médecin résident
//! \return salaire annuel du médecin résident (=salaire de base du médecin résidant + nombre de consultations * le prix de consultation du médecin)
double MedecinResident::getSalaireAnnuel() const
{
	double salaireAnnuel;
	salaireAnnuel = SALAIRE_DE_BASE_MEDECIN_RESIDENT + nbConsultations_ * getPrixConsultation();
	return salaireAnnuel;
}


