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
	std::vector<std::shared_ptr<Patient>> patientsAssocies = medecin_->getPatientsAssocies();
	if (medecin.chercherPatient(patient.getNumeroAssuranceMaladie()) == nullptr) {
		medecin += patient;
	};
}


// TODO : operateur<< pour afficher les informations d'une consultation.
// Voir l'enoncé pour avoir un exemple d'affichage d'une consultation. 
// Si l'affichage n'est pas respecté, le test de l'affichage de consultation ne passera pas.
std::ostream& operator<<(std::ostream& string, const Consultation& consultation) {

	return string <<"Consultation: \n"
		<< "Medecin: "<< consultation.medecin_->getNom() << "\n"
		<<"Patient: "<< consultation.patient_->getNom()<<" | Date de naissance: "<< consultation.patient_->getDateDeNaissance()<< " | Numero d'assurance maladie: "<< consultation.patient_->getNumeroAssuranceMaladie()<< "\n"
		<<"Date de consultation: "<< consultation.date_<<"\n";
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
