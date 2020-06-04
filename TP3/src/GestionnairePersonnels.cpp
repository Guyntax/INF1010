//! Implémentation de la classe GestionnairePersonnels qui permet la gestion des personnels de l’hôpital.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#include "GestionnairePersonnels.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

constexpr int PERSONNEL_INEXSISTANT = -1;

//! Méthode qui cherche un personnel par son id
//! \param id L'identifiant du personnel à chercher
Personnel* GestionnairePersonnels::chercherPersonnel(const std::string& id)
{
	for (const auto& personnel : personnels_)
	{
		if (*personnel == id)
		{
			return personnel.get();// return Un pointeur vers le personnel. 
		}
	}
	return nullptr; // Le pointeur est nullptr si le personnel n'existe pas dans la liste des personnels.
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
			if (!lireLignePersonnel(ligne)) // Lit chaque ligne et retourne false si il y a un probleme
			{
				return false;
			}
		}
		return true; // retourne true si toutes les ignes on été lues sans problemes
	}
	std::cerr << "Le fichier " << nomFichier
		<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";

	return false;// retourne false si le ficher ne s'ouvre pas
}

//! Operateur qui ajoute un personnel à la liste des personnels
//! \param personnel Le personnel à ajouter
//! \return          Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePersonnels::operator+=(Personnel* personnel)
{
	if (personnel && !chercherPersonnel(personnel->getId()))
	{
		// Vérifier si personnel est un MedecinResident
		if (dynamic_cast<MedecinResident*>(personnel)) {
			personnels_.push_back(std::make_shared<MedecinResident>(*dynamic_cast<MedecinResident*>(personnel)));
		}
		//Vérifie si personnel est un Medecin
		else if (dynamic_cast<Medecin*>(personnel)) {
			personnels_.push_back(std::make_shared<Medecin>(*dynamic_cast<Medecin*>(personnel)));
		}	
		else {
			assert(false);
		}
		return true; // retourne true si le patient a bel et bien été ajouté
	}
	return false;// retourne false si le MEdecin existe deja dans le gesttionnaire
}

//! Operateur qui supprime un personnel de la liste des personnels en rendant son statut estActif à false
//! \param id	  L'identifiant du personnel à supprimer
bool GestionnairePersonnels::operator-=(const std::string& id)
{
	int indexPersonnel = trouverIndexPersonnel(id);
	if (indexPersonnel != PERSONNEL_INEXSISTANT) // on le supprime seulement s'il existe
	{
		personnels_[indexPersonnel]->setEstActif(false);
		return true;
	}
	//! \return  Un bool qui indique si l'opération a bien fonctionnée
	return false;
}

//! Operateur qui permet d'afficher les informations des personnels 
//! \param os					   Le stream dans lequel afficher
//! \param gestionnairePersonnels  Le gestionnaire personnels à afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePersonnels)
{
	for (const auto& personnel : gestionnairePersonnels.personnels_)
	{
		(personnel)->afficher(os);
		os << '\n';
	}
	return os; // Le ostream est retourné par référence
}

//! Méthode qui retourne la liste de tout le personnel de l'hôpital
const std::vector<std::shared_ptr<Personnel>>& GestionnairePersonnels::getPersonnels() const
{
	//! \return personnels_ la liste du personnel
	return personnels_;
}


//! Méthode qui retourne la liste de tous les médecins de l'hôpital
std::vector<Medecin*> GestionnairePersonnels::getMedecins() const
{
	std::vector<Medecin*> temp;
	for (const auto& personnel : personnels_) {
		if (dynamic_cast<Medecin*>(personnel.get())) {
			temp.push_back(dynamic_cast<Medecin*>(personnel.get()));
		}
	}
	//! \return vecteur qui contient les pointeurs de tous les médecins
	return  temp;
}

//! Méthode qui retourne la liste de tous les médecins résidents de l'hôpital
std::vector<MedecinResident*> GestionnairePersonnels::getMedecinsResidents() const
{
	std::vector<MedecinResident*> temp;
	for (const auto& personnel : personnels_) {
		if (dynamic_cast<MedecinResident*>(personnel.get())) {
			temp.push_back(dynamic_cast<MedecinResident*>(personnel.get()));
		}
	}
	//! \return vecteur qui contient les pointeurs de tous les médecins résidents
	return  temp;
}


//! Méthode qui retourne le nombre de personnel
size_t GestionnairePersonnels::getNbPersonnels() const {
	return personnels_.size(); //! \return nombre de personnel
}

//! Méthode qui retourne le nombre de médecins
size_t GestionnairePersonnels::getNbMedecins() const {
	return getMedecins().size(); //! \return nombre de médecins
}

//! Méthode qui retourne le nombre de médecins résidents
size_t GestionnairePersonnels::getNbMedecinsResidents() const {
	return getMedecinsResidents().size(); //! \return nombre de médecins résidents
}

//! Méthode qui lit les attributs d'un personnel
//! \param ligne  Le string qui contient les attributs
//! \return bool qui dit si la ligne a bien été lue
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
		GestionnairePersonnels::TypePersonnel typePersonnel = to_enum<GestionnairePersonnels::TypePersonnel, int>(indexTypePersonnel);
	
		switch (typePersonnel) {
		case GestionnairePersonnels::TypePersonnel::Medecin : //Medecin
			stream >> indexSpecialite;
			// Ajoute le pointer nouvelment créé et retoune true, si c'est un succès
			return operator+=(std::make_shared<Medecin>(Medecin(nomPersonnel, id, Medecin::Specialite(indexSpecialite))).get());
			
		case GestionnairePersonnels::TypePersonnel::MedecinResident: //MedecinResident
			stream >> std::quoted(dateDeNaissance) >> std::quoted(matricule) >> std::quoted(etablissement) >> indexSpecialite;
			// Ajoute le pointer nouvelment créé et retoune true, si c'est un succès
			return operator+=(std::make_shared<MedecinResident>(MedecinResident(nomPersonnel, dateDeNaissance, matricule, etablissement, id, Medecin::Specialite(indexSpecialite))).get());
			
		default:
			assert(false); // ne devrait pas passer avec le fichier fourni
		}
	}
	return false; // retourne false si on ne peut pas lire à partir du stream
}

//! Méthode  qui permet de trouver l'index un medecin dans la liste des medecins
//! \param numeroLicence   numero de licence du medecin
int GestionnairePersonnels::trouverIndexPersonnel(const std::string& id)
{
	for (std::size_t i = 0; i < personnels_.size(); i++)
	{
		if (*personnels_[i] == id)
		{
			return static_cast<int>(i);
		}
	}
	//! \return int bool qui indique l'index du medecin et MEDECIN_INEXSISTANT si le medecin est inexistant
	return PERSONNEL_INEXSISTANT;
}
