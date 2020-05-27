#include "GestionnairePersonnels.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

constexpr int PERSONNEL_INEXSISTANT = -1;

//! Méthode qui cherche un personnel par son id
//! \param id L'identifiant du personnel à chercher
//! \return Un pointeur vers le personnel. Le pointeur est nullptr si le personnel n'existe pas dans la liste des personnels.
Personnel* GestionnairePersonnels::chercherPersonnel(const std::string& id)
{
	for (const auto& personnel : personnels_)
	{
		if (*personnel == id)
		{
			return personnel.get();
		}
	}

	return nullptr;
}

//! Méthode  qui permet de charger les informations des personnels
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succes
bool GestionnairePersonnels::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		personnels_.clear();
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (!lireLignePersonnel(ligne))
			{
				return false;
			}
		}
		return true;
	}
	std::cerr << "Le fichier " << nomFichier
		<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";

	return false;
}

//! Operateur qui ajoute un personnel à la liste des personnels
//! \param personnel Le personnel à ajouter
//! \return          Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePersonnels::operator+=(Personnel* personnel)
{
	if (personnel && !chercherPersonnel(personnel->getId()))
	{
		//TODO : vérifier si personnel est un MedecinResidant. Conversion dynamique
		if (....) {
			//TODO : Ajouter un objet de type MedecinResident au personnels_. Conversion dynamique
		}
		//TODO : vérifier si personnel est un Medecin. Conversion dynamique
		else if (...) {
			//TODO : Ajouter un objet de type Medecin au personnels_. Conversion dynamique
		}
		else {
			assert(false);
		}

		return true;
	}

	return false;
}

//! Operateur qui supprime un personnel de la liste des personnels en rendant son statut estActif à false
//! \param id	  L'identifiant du personnel à supprimer
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePersonnels::operator-=(const std::string& id)
{
	int indexPersonnel = trouverIndexPersonnel(id);
	if (indexPersonnel != PERSONNEL_INEXSISTANT)
	{
		personnels_[indexPersonnel]->setEstActif(false);
		return true;
	}

	return false;
}

//! Operateur qui permet d'afficher les informations des personnels 
//! \param os					   Le stream dans lequel afficher
//! \param gestionnairePersonnels  Le gestionnaire personnels à afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePersonnels)
{
	for (const auto& personnel : gestionnairePersonnels.personnels_)
	{
		//TODO : Afficher les information d'un personnel
		os << '\n';
	}

	return os;
}

//! Méthode qui retourne la liste de tout le personnel de l'hôpital
//! \return personnels_ la liste du personnel
const std::vector<std::shared_ptr<Personnel>>& GestionnairePersonnels::getPersonnels() const
{
	return personnels_;
}

//TODO : Méthode getMedecins
//Hint : conversion dynamique
//Chercher les médecins  parmis tous les personnels 
//Retourner un vecteur de Medecin*


//TODO : Méthode getMedecinsResidents
//Hint : conversion dynamique
//Chercher les médecins résidents  parmis tous les personnels 
//Retourner un vecteur de MedecinResident*


// TODO : Méthode getNbPersonnels
// Retourner le nombre des personnels

// TODO : Méthode getNbMedecins
// Retourner le nombre de medecins


// TODO : Méthode getNbMedecinsResidents
// Retourner le nombre de medecins résidents



//! Méthode qui lit les attributs d'un personnel
//! \param ligne  Le string qui contient les attributs
bool GestionnairePersonnels::lireLignePersonnel(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePersonnel;
	std::string nomPersonnel;
	std::string id;

	std::string dateDeNaissance;
	std::string matricule;
	std::string etablissement;

	int indexSpecialite;

	if (stream >> indexTypePersonnel >> std::quoted(nomPersonnel) >> std::quoted(id))
	{
		//TODO : 
		//1- Utiliser to_enum pour convertir indexTypePersonnel à l'enum TypePersonnel : to_enum<GestionnairePersonnels::TypePersonnel, int>(variable)
		//2- Si le personnel est de type Medecin. 
		//	  - Lire indexPecialite
		//	  - Ajouter un objet de type Medecin en utilisant l'opérateur +=
		//3- Si le personnel est de type MedecinResident: 
		//    - Lire sa date de naissance, son matricule, son établissement et  indexSpecialite
		//    - Ajouter un objet de type MedecinResidant en utilisant l'opérateur +=
		// 
		switch () {

		default:
			assert(false); // ne devrait pas passer avec le fichier fourni
		}
	}

	return false;
}

//! Méthode  qui permet de trouver l'index un medecin dans la liste des medecins
//! \param numeroLicence   numero de licence du medecin
//! \return             int bool qui indique l'index du medecin et MEDECIN_INEXSISTANT si le medecin est inexistant
int GestionnairePersonnels::trouverIndexPersonnel(const std::string& id)
{
	for (std::size_t i = 0; i < personnels_.size(); i++)
	{
		if (*personnels_[i] == id)
		{
			return static_cast<int>(i);
		}
	}
	return PERSONNEL_INEXSISTANT;
}
