//! Définition de la classe ConsultationPhysique qui hérite de Consultation.
//! Cette classe permet de gérer les consultations physiques de l’hôpital.
//! \Authurs: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#ifndef CONSULTATIONPHYSIQUE_H
#define CONSULTATIONPHYSIQUE_H

#include <string>
#include "Consultation.h"
#include "PatientEtudiant.h"






//DONE: Cette classe hérite de la classe Consultaion.
class ConsultationPhysique : public Consultation //DONE : Cette classe hérite de la classe Consultaion.
{
public:
	//DONE: Le constructeur par paramètres pour initialiser les attributs de la classe. 
	// Ce constructeur utilise le constructeur de la classe Consultation.
	ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date);


	//DONE: surchage de la méthode calculerPrix 
	const double calculerPrix() const;

	//DONE: des getters et des setters si necessaire
	void setPrescription(std::string prescription);
	std::string getPrescription()const;



private:
	//DONE: Des attributs privées :prescription_ (std::string)
	std::string prescription_;
};



#endif // CONSULTATIONPHYSIQUE_H#pragma once
