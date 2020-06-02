//! Implémentation de la classe ConsultationPhysique qui hérite de Consultation.
//! Cette classe permet de gérer les consultations physiques de l’hôpital.
//! \Authurs: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020


#include <string>
#include "ConsultationPhysique.h"

//! Constructeur par paramètres
//! \param medecin	Medecin qui effectue la consultation
//! \param patient	Patient qui reçoit la consultation
//! \param date		Date de la consultation
ConsultationPhysique::ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date) :
	Consultation(medecin, patient, date),
	prescription_(" ")
{}


//! Méthode qui calcule le prix de la consultation
//! \return  le prix de la consultation
const double ConsultationPhysique::calculerPrix() const {
	double prix = medecin_->getPrixConsultation();
	if (dynamic_cast<PatientEtudiant*>(patient_))// Vérifier si le patient est un patient étudiant
	{
		prix = prix * (1 - dynamic_cast<PatientEtudiant*>(patient_)->getTauxRabais());
	}
	return prix;
}


//! Méthode qui permet de faire une prescription
//! \param diagnostique	string qui contient la prescription
void ConsultationPhysique::setPrescription(std::string prescription) {
	prescription_ = prescription;
}

//! Méthode qui retourne les prescriptions de la consultation
//! \return	string qui contient la prescription
std::string ConsultationPhysique::getPrescription()const {
	return prescription_;
}

