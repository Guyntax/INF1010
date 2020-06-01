//! Implémentation de la classe ConsultationPhysique qui hérite de Consultation.
//! \Authurs: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020


#include <string>
#include "ConsultationPhysique.h"

//DONE : Constructeur par paramètres
ConsultationPhysique::ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date) :
	Consultation(medecin, patient, date),
	prescription_(" ")
{}
//DONE : const double calculerPrix() const
// Chercher le prix de la consultation du médecin
// Vérifier si le patient est un patient étudiant (Convesion dynamique)
// Si le patient est patient étudiant, appliquer  le rabais étudiant
// retourner le prix de la consultaion
const double ConsultationPhysique::calculerPrix() const {
	double prix = medecin_->getPrixConsultation();
	if (dynamic_cast<PatientEtudiant*>(patient_)) {
		prix = prix * (1 - dynamic_cast<PatientEtudiant*>(patient_)->getTauxRabais());
	}
	return prix;
}


// DONE : des getters et des setters si nécessaire
void ConsultationPhysique::setPrescription(std::string prescription) {
	prescription_ = prescription;
}

std::string ConsultationPhysique::getPrescription()const {
	return prescription_;
}

