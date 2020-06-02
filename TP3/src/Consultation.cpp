//! Implémentation de la classe abstraite Consultation qui permet de gérer les consultations de l’hôpital.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#include "Consultation.h"
#include <iostream>
#include <string>

//! Constructeur par paramètres de la classe abstraite Consultation
//! \param medecin Le medecin responsable de la consultation
//! \param patient Le patient qui demande une consultation
//! \param date    La date de la consultation
Consultation::Consultation(Medecin& medecin, Patient& patient, const std::string& date) :
	medecin_(&medecin), patient_(&patient), date_(date), prix_(PRIX_DE_BASE)
{
}



//! Méthode qui retourne le médecin de la consultation
//! \return medecin_ le pointeur vers le médecin de la consultation
Medecin* Consultation::getMedecin() const
{
	return medecin_;
}


//! Méthode qui retourne le patient de la consultation
//! \return patient_ le pointeur vers le patient de la consultation
Patient* Consultation::getPatient() const
{
	return patient_;
}

//! Méthode qui retourne la date de la consultation
//! \return date_ la date de la consultation
const std::string& Consultation::getDate() const
{
	return date_;
}


//! Méthode qui affiche les informations d'une consultation
//! \param os Le stream dans lequel afficher
void Consultation::afficher(std::ostream& os) const
{
	// Chercher le nom de la classe. Elle peut être ConsultationEnligne ou ConsultationPhysique.
	std::string typeConsultation = typeid(*this).name();//Utiliser typeid().name()
	typeConsultation.erase(0, 6); // Efface "Class "

	// Chercher le nom de la classe.Elle peut être Medecin ou MedecinResident.
	std::string typeMedecin = typeid(*medecin_).name();//Utiliser typeid().name() ;
	typeMedecin.erase(0, 6); // Efface "Class "

	// Chercher le nom de la classe. Elle peut être Patient ou PatientEtudiant.
	std::string typePatient = typeid(*patient_).name();//Utiliser typeid().name()
	typePatient.erase(0, 6); // Efface "Class "					  

	os << "Consultation: "
		<< "\n\tType: " << typeConsultation//Extraire le nom de la classe du string typeConsultation
		<< "\n\t\t" << typeMedecin//Extraire le nom de la classe du string typeMedecin
		<< ": " << medecin_->getId() // afficher Id du medecin
		<< "\n\t\t" << typePatient//Extraire le nom de la classe du string typePatient 
		<< ": " << patient_->getNumeroAssuranceMaladie()// afficher le numero d'assurance maladie du patient
		<< "\n\t\t" << "Date de consultation: " << date_ << "\n"; //Afficher date_
}