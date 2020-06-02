//! Impl�mentation de la classe ConsultationPhysique qui h�rite de Consultation.
//! Cette classe permet de g�rer les consultations physiques de l�h�pital.
//! \Authurs: Didier Blach-Lafl�che & Maude Tremblay
//! \date 07 Juin 2020


#include <string>
#include "ConsultationPhysique.h"

//! Constructeur par param�tres
//! \param medecin	Medecin qui effectue la consultation
//! \param patient	Patient qui re�oit la consultation
//! \param date		Date de la consultation
ConsultationPhysique::ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date) :
	Consultation(medecin, patient, date),
	prescription_(" ")
{}


//! M�thode qui calcule le prix de la consultation
//! \return  le prix de la consultation
const double ConsultationPhysique::calculerPrix() const {
	double prix = medecin_->getPrixConsultation();
	if (dynamic_cast<PatientEtudiant*>(patient_))// V�rifier si le patient est un patient �tudiant
	{
		prix = prix * (1 - dynamic_cast<PatientEtudiant*>(patient_)->getTauxRabais());
	}
	return prix;
}


//! M�thode qui permet de faire une prescription
//! \param diagnostique	string qui contient la prescription
void ConsultationPhysique::setPrescription(std::string prescription) {
	prescription_ = prescription;
}

//! M�thode qui retourne les prescriptions de la consultation
//! \return	string qui contient la prescription
std::string ConsultationPhysique::getPrescription()const {
	return prescription_;
}

