//! Définition de la classe ConsultationEnligne qui hérite de Consultation.
//! Cette classe permet de gérer les consultations en ligne de l’hôpital.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#ifndef CONSULTATIONENLIGNE_H
#define CONSULTATIONENLIGNE_H

#include <string>
#include "Consultation.h"
#include "PatientEtudiant.h"

class ConsultationEnligne : public Consultation 
{
public:


	ConsultationEnligne(Medecin& medecin, Patient& patient, const std::string& date);

	const double calculerPrix() const override;

	void setDiagnostique(std::string diagnostique);
	std::string getDiagnostique()const;

	static constexpr double TAUX_RABAIS_CONSULTATION_ENLIGNE = 0.5;

private:
	std::string diagnostique_;
	double rabaisConsultationEnLigne_;
};

#endif // CONSULTATIONENLIGNE_H