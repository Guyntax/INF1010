//! Définition de la classe ConsultationEnligne qui hérite de Consultation.
//! Cette classe permet de gérer les consultations en ligne de l’hôpital.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#ifndef CONSULTATIONENLIGNE_H
#define CONSULTATIONENLIGNE_H

#include <string>
#include "Consultation.h"
#include "PatientEtudiant.h"

class ConsultationEnligne : public Consultation //DONE : Cette classe hérite de la classe Consultaion.
{
public:

	//DONE: Le constructeur par paramètres pour initialiser les attributs de la classe. 
	//Ce constructeur utilise le constructeur de la classe Consultation.
	ConsultationEnligne(Medecin& medecin, Patient& patient, const std::string& date);

	//DONE : surchager la méthode calculerPrix  const double calculerPrix() const override;
	const double calculerPrix() const override;

	//DONE: des getters et des setters si necessaire
	void setDiagnostique(std::string diagnostique);
	std::string getDiagnostique()const;

	static constexpr double TAUX_RABAIS_CONSULTATION_ENLIGNE = 0.5;
private:
	//DONE : Des attributs privées : diagnostique__ (std::string),rabaisConsultationEnLigne__ (double)
	std::string diagnostique_;
	double rabaisConsultationEnLigne_;
};

#endif // CONSULTATIONENLIGNE_H