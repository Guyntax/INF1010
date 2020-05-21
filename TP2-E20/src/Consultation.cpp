//! Implémentation de la classe Consultation qui permet la gestion des consultations de l'hôpital
//! \authors Didier Blach Laflèche & Maude Tremblay
//! \date 21 Mai 2020

#include "Consultation.h"
#include "Medecin.h"
#include "Patient.h"
#include <iostream>
#include <string>
#include <vector>
#include<sstream>


//! Contructeur par paramètres
Consultation::Consultation(Medecin& medecin, Patient& patient, const std::string& date)
	:medecin_(&medecin)
	,patient_(&patient)
	, date_(date){
	std::vector<std::shared_ptr<Patient>> patientsAssocies = medecin_->getPatientsAssocies();
	if (medecin.chercherPatient(patient.getNumeroAssuranceMaladie()) == nullptr) {
		medecin += patient;
	};
}


//Surcharge de l'operateur<< : afficher les informations d'une consultation.
//! \param stream Le stream dans lequel afficher
//! \param consultation Consultation dont on veut afficher les informations
//! \return stream Le stream dans lequel les informations sont affichées
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
