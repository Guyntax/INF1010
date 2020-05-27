// TODO: Faire l'entête de fichier
#include "Consultation.h"
#include <iostream>
#include <string>

//! Constructeur par paramètres de la classe abstraite Consultation
//! \param medecin Le medecin responsable de la consultation
//! \param patient Le patient qui demande une consultation
//! \param date    La date de la consultation
Consultation::Consultation(Medecin& medecin, Patient& patient, const std::string& date) :
	medecin_(&medecin), patient_(&patient), date_(date)
{
}

//! Méthode qui affiche les informations d'une consultation
//! \param os Le stream dans lequel afficher
void Consultation::afficher(std::ostream& os) const
{

	std::string typeConsultation =  //TODO: Chercher le nom de la classe. Elle peut être ConsultationEnligne ou ConsultationPhysique.
								  //Utiliser typeid().name()
	std::string typeMedecin =  //TODO: Chercher le nom de la classe.Elle peut être Medecin ou MedecinResident.
		                        //Utiliser typeid().name() ;
	std::string typePatient = //TODO: Chercher le nom de la classe. Elle peut être Patient ou PatientEtudiant.
		                      //Utiliser typeid().name()
	os << "Consultation: "
		<< "\n\tType: " << //Extraire le nom de la classe du string typeConsultation
		<< "\n\t\t" << //Extraire le nom de la classe du string typeMedecin << ": " << // afficher Id du medecin
		<< "\n\t\t" << //Extraire le nom de la classe du string typePatient  << ": " << // afficher le numero d'assurance maladie du patient
		<< "\n\t\t" << "Date de consultation: " << //Afficher date_
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
