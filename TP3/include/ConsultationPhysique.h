#ifndef CONSULTATIONPHYSIQUE_H
#define CONSULTATIONPHYSIQUE_H

#include <string>
#include "Consultation.h"
#include "PatientEtudiant.h"






//TODO: Cette classe h�rite de la classe Consultaion.
class ConsultationPhysique : public Consultation //DONE : Cette classe h�rite de la classe Consultaion.
{
public:
	//TODO: Le constructeur par param�tres pour initialiser les attributs de la classe. 
	// Ce constructeur utilise le constructeur de la classe Consultation.
	ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date);


	//TODO: surchage de la m�thode calculerPrix 
	const double calculerPrix() const;

	//TODO: des getters et des setters si necessaire
	void setPrescription(std::string prescription);
	std::string getPrescription()const;



private:
	//TODO: Des attributs priv�es :prescription_ (std::string)
	std::string prescription_;
};



#endif // CONSULTATIONPHYSIQUE_H#pragma once
