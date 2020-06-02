//! Implémentation de la classe ConsultationEnligne qui hérite de Consultation.
//! Cette classe permet de gérer les consultations en ligne de l’hôpital.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020


#include "ConsultationEnligne.h"
#include <string>


//! Constructeur par paramètres
//! \param medecin	Médecin qui s'occupe de la consultation
//! \param patient	Patient
//! \param date		Date de la consultation
ConsultationEnligne::ConsultationEnligne(Medecin& medecin, Patient& patient, const std::string& date):
	Consultation(medecin, patient, date),
	diagnostique_(" "),
	rabaisConsultationEnLigne_(TAUX_RABAIS_CONSULTATION_ENLIGNE)
{} 

//! Méthode qui calcule le prix de la consultation du médecin
//! \return le prix de la consultaion
const double ConsultationEnligne::calculerPrix() const  {
	double prix = medecin_->getPrixConsultation();
	if (dynamic_cast<PatientEtudiant*>(patient_)) // Vérifie si le patient est un patient étudiant
	{
		prix = prix * ( 1 -  dynamic_cast<PatientEtudiant*>(patient_)->getTauxRabais() );
	}
	prix = prix * (1 - rabaisConsultationEnLigne_ );

	return prix;
}


//! Méthode qui permet de poser un diagnostique
//! \param diagnostique	string qui contient le diagnostique
void ConsultationEnligne::setDiagnostique(std::string diagnostique) { diagnostique_ = diagnostique; }

//! Méthode qui permet d'obtenir le diagnostique
//! \return string qui contient le diagnostique
std::string ConsultationEnligne::getDiagnostique() const { return diagnostique_; }








