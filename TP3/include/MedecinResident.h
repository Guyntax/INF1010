//! Définition de la classe MedecinResident qui représente un médecin résident qui exerce à l’hôpital
//! Cette classe hérite de Personnel et de Étudiant.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#ifndef MEDECINRESIDENT_H
#define MEDECINRESIDENT_H
#include "Etudiant.h"
#include "Medecin.h"

#include <string>

class MedecinResident : public Etudiant, public Medecin {

	public:
	
	MedecinResident(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule,const std::string& etablissement,
		const std::string& numeroLicence, Medecin::Specialite specialite);

	void afficher(std::ostream& stream) const override;
	double getSalaireAnnuel() const override;

	static constexpr size_t SALAIRE_DE_BASE_MEDECIN_RESIDENT = 50000;

};

#endif // MEDECINRESIDENT_H