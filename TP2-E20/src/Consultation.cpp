// TODO: Faire l'entête de fichier

#include "Consultation.h"
#include "Medecin.h"
#include "Patient.h"
#include <iostream>
#include <string>
#include <vector>
#include<sstream>


// Contructeur par param^tres
Consultation::Consultation(Medecin& medecin, Patient& patient, const std::string& date)
	:medecin_(&medecin)
	,patient_(&patient)
	, date_(date){
	// TODO : compléter Constructeur par paramètre de la classe Consulation en utilisant la liste d'initialisation
	// Assurer d'ajouter le patient à la liste des patients assoicés au medecin s'il n'y existe pas.
	std::unique_ptr<std::vector<Patient>> patientsAssocies = medecin_->getPatientsAssocies();

	// bla bla

}


// TODO : operateur<< pour afficher les informations d'une consultation.
// Voir l'enoncé pour avoir un exemple d'affichage d'une consultation. 
// Si l'affichage n'est pas respecté, le test de l'affichage de consultation ne passera pas.
std::stringstream& Consultation::operator<<(std::stringstream& string) {


}

//! Méthode qui retourne le médecin de la consultation
//! \return Medecin*
Medecin* Consultation::getMedecin() const
{
	return medecin_;
}

//! Méthode qui retourne le patient de la consultation
//! \return Patient*
Patient* Consultation::getPatient() const
{
	return patient_;
}

//! Méthode qui retourne lea date de la consultation
//! \return const std::string
const std::string& Consultation::getDate() const
{
	return date_;
}
