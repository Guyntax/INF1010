//! Définition de la classe Étudiant. Celle-ci hérite de Patient et de Étudiant.
//! \Authurs: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#ifndef PATIENTETUDIAT_H
#define PATIENTETUDIAT_H

#include "Patient.h"
#include "Etudiant.h"
#include <iostream>


//DONE : Classe qui hérite de la classe Etudiant et la classe Patient
class PatientEtudiant : public Patient, public Etudiant
{
public:
	PatientEtudiant() = default;
	
	//DONE : Constructeur par paramètre. Il utilise le constructeur de la classe Etudiant et la classe Patient
	PatientEtudiant(const std::string & nom, const std::string & dateDeNaissance, const std::string & numeroAssuranceMaladie, const std::string & matricule, const std::string & etablissement);

	//DONE : surcharge de la méthode afficher
	void afficher(std::ostream& stream)const;

	//Des getters et des setters si nécessaire.
	double getTauxRabais() const;

	const double TAUX_RABAIS = 0.2;

private:
	double tauxRabais_;
};

#endif // PATIENTETUDIAT_H