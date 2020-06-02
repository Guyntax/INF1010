//! Définition de la classe MedecinResident qui hérite de Personnel et de Étudiant.
//! \Authurs: Didier Blach-Laflèche & Maude Tremblay
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

//TODO: 
//Cette classe hérite de la classe Etudiant et la classe Medecin
//Pas d'attributs spéciaux pour cette classe
//Un constructeur par paramètre pour intialiser les attributs en faisant appel au constructeur des classes Etudiant et Medecin
//Surchage de la méthode afficher
//Surchage de la méthode getSalaireAnnuel
//Un salaire de base comme constante static :   static constexpr size_t SALAIRE_DE_BASE_MEDECIN_RESIDENT = 50000;


#endif // MEDECINRESIDENT_H