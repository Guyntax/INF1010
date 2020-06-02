//! Définition de la classe Étudiant qui représente un patient qui est étudiant. Celle-ci hérite de Patient et de Étudiant.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#ifndef PATIENTETUDIAT_H
#define PATIENTETUDIAT_H

#include "Patient.h"
#include "Etudiant.h"
#include <iostream>


class PatientEtudiant : public Patient, public Etudiant
{
public:
	PatientEtudiant() = default;
	
	PatientEtudiant(const std::string & nom, const std::string & dateDeNaissance, const std::string & numeroAssuranceMaladie, const std::string & matricule, const std::string & etablissement);

	void afficher(std::ostream& stream)const;

	double getTauxRabais() const;

	const double TAUX_RABAIS = 0.2;

private:
	double tauxRabais_;
};

#endif // PATIENTETUDIAT_H