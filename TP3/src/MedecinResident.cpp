//! Implémentation de la classe MedecinResident qui hérite de Personnel et de Étudiant.
//! \Authurs: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020


#include <iostream>
#include <string>
#include "MedecinResident.h"


MedecinResident::MedecinResident(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, 
	const std::string& etablissement, const std::string& numeroLicence, Medecin::Specialite specialite):
	Etudiant(nom,dateDeNaissance,matricule,etablissement),
	Medecin(nom,numeroLicence,specialite){}


// DONE : Méthode afficher
// 1- Afficher les informations liées à la classe Medecin
// 2- Afficher "\n\t"
// 3- // 1- Afficher les informations liées à la classe Etudiant
void MedecinResident::afficher(std::ostream& stream) const
{
	Medecin::afficher(stream);
	stream << "\n\t";
	Etudiant::afficher(stream);
}

double MedecinResident::getSalaireAnnuel() const
{
	double salaireAnnuel;
	salaireAnnuel = SALAIRE_DE_BASE_MEDECIN_RESIDENT + nbConsultations_ * getPrixConsultation();
	return salaireAnnuel;
}

// DONE: //Un constructeur par paramètre pour intialiser les attributs en faisant appel au constructeur des classes Etudiant et Medecin




// DONE : Méthode getSalaireAnnuel
// Retourner le Salaire annuel qui est:  salaire de base du médecin résidant + nombre de consultations * le prix de consultation du médecin

