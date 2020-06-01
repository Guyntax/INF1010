//TODO : Ent�te du ficher

#include <string>
#include "ConsultationPhysique.h"

//TODO : Constructeur par param�tres
ConsultationPhysique::ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date) :
	Consultation(medecin, patient, date),
	prescription_(" ")
{}
//TODO : const double calculerPrix() const
// Chercher le prix de la consultation du m�decin
// V�rifier si le patient est un patient �tudiant (Convesion dynamique)
// Si le patient est patient �tudiant, appliquer  le rabais �tudiant
// retourner le prix de la consultaion
const double ConsultationPhysique::calculerPrix() const {
	double prix = medecin_->getPrixConsultation();
	if (dynamic_cast<PatientEtudiant*>(patient_)) {
		prix = prix * (1 - dynamic_cast<PatientEtudiant*>(patient_)->getTauxRabais());
	}
	return prix;
}


// TODO : des getters et des setters si n�cessaire
void ConsultationPhysique::setPrescription(std::string prescription) {
	prescription_ = prescription;
}

std::string ConsultationPhysique::getPrescription()const {
	return prescription_;
}

