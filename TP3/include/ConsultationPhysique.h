//! Définition de la classe ConsultationPhysique qui hérite de Consultation.
//! Cette classe permet de gérer les consultations physiques de l’hôpital.
//! \Authurs: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#ifndef CONSULTATIONPHYSIQUE_H
#define CONSULTATIONPHYSIQUE_H

#include <string>
#include "Consultation.h"
#include "PatientEtudiant.h"


class ConsultationPhysique : public Consultation 
{
public:
	ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date);

	const double calculerPrix() const;

	void setPrescription(std::string prescription);
	std::string getPrescription()const;

private:
	
	std::string prescription_;
};



#endif // CONSULTATIONPHYSIQUE_H#pragma once
