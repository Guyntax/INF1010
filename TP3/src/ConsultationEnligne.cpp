//TODO : Entête du ficher
#include "ConsultationEnligne.h"
#include <string>


// TODO : Constructeur par paramètres
ConsultationEnligne::ConsultationEnligne(Medecin& medecin, Patient& patient, const std::string& date):
	Consultation(medecin, patient, date),
	diagnostique_(" "),
	rabaisConsultationEnLigne_(TAUX_RABAIS_CONSULTATION_ENLIGNE)
{} 

//TODO : const double calculerPrix() const
// Chercher le prix de la consultation du médecin
// Vérifier si le patient est un patient étudiant (Convesion dynamique)
// Si le patient est patient étudiant, appliquer  le rabais étudiant
// Appliquer encore le rabais de la consultation enligne
// retourner le prix de la consultaion
const double ConsultationEnligne::calculerPrix() const  {
	double prix = medecin_->getPrixConsultation();
	if (dynamic_cast<PatientEtudiant*>(patient_)) {
		prix = prix * ( 1 -  dynamic_cast<PatientEtudiant*>(patient_)->getTauxRabais() );
	}
	prix = prix * (1 - rabaisConsultationEnLigne_ );

	return prix;
}

// TODO : des getters et des setters si nécessaire
void ConsultationEnligne::setDiagnostique(std::string diagnostique) { diagnostique_ = diagnostique; }
std::string ConsultationEnligne::getDiagnostique() const { return diagnostique_; }








