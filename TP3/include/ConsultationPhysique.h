//! D�finition de la classe ConsultationPhysique qui h�rite de Consultation.
//! Cette classe permet de g�rer les consultations physiques de l�h�pital.
//! \Authurs: Didier Blach-Lafl�che & Maude Tremblay
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
