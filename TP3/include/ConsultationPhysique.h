//! D�finition de la classe ConsultationPhysique qui h�rite de Consultation.
//! Cette classe permet de g�rer les consultations physiques de l�h�pital.
//! \Authurs: Didier Blach-Lafl�che & Maude Tremblay
//! \date 07 Juin 2020

#ifndef CONSULTATIONPHYSIQUE_H
#define CONSULTATIONPHYSIQUE_H

#include <string>
#include "Consultation.h"
#include "PatientEtudiant.h"






//DONE: Cette classe h�rite de la classe Consultaion.
class ConsultationPhysique : public Consultation //DONE : Cette classe h�rite de la classe Consultaion.
{
public:
	//DONE: Le constructeur par param�tres pour initialiser les attributs de la classe. 
	// Ce constructeur utilise le constructeur de la classe Consultation.
	ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date);


	//DONE: surchage de la m�thode calculerPrix 
	const double calculerPrix() const;

	//DONE: des getters et des setters si necessaire
	void setPrescription(std::string prescription);
	std::string getPrescription()const;



private:
	//DONE: Des attributs priv�es :prescription_ (std::string)
	std::string prescription_;
};



#endif // CONSULTATIONPHYSIQUE_H#pragma once
