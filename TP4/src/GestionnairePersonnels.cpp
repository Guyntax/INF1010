//TODO Entête du fichier

#include "GestionnairePersonnels.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

constexpr int PERSONNEL_INEXSISTANT = -1;

//TODO : Modifier cette méthode 
// Cette méthode doit utiliserla fonction find
// Consulter l'énoncer pour cette méthode pour voir plus d'explication
// Le nombre des lignes de code maximale est 4 lignes (sans compter la signature, les lignes vides et les lignes avec accolades)
Personnel* GestionnairePersonnels::chercherPersonnel(const std::string& id) const
{
	for (auto& personnel : personnels_)
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

// TODO: Remplacer l'opérateur par la méthode générique ajouterPatient
// La méthode prend une référence vers l'objet à jouter
// L'implémentation doit être modifié aussi
// Le nombre des lignes de code maximale est 3 lignes (sans compter la signature, les lignes vides et les lignes avec accolades)
bool GestionnairePersonnels::operator+=(Personnel* personnel)
{
	if (personnel && !chercherPersonnel(personnel->getId()))
	{
		if (dynamic_cast<MedecinResident*>(personnel)) {
			personnels_.push_back(std::make_shared<MedecinResident>(*dynamic_cast<MedecinResident*>(personnel)));
		}
		else if (dynamic_cast<Medecin*>(personnel)) {
			personnels_.push_back(std::make_shared<Medecin>(*dynamic_cast<Medecin*>(personnel)));
		}
		else {
			assert(false);
		}

		return true;
	}

	return false;
}

// TODO: Remplacer l'opérateur par la méthode supprimerPesonnel
// La méthode prend un string qui est l'id de personnel à supprimer
bool GestionnairePersonnels::operator-=(const std::string& id)
{
	//TODO : utiliser la méthode chercherPersonnel
	if ()
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
	// Code fourni
	if constexpr (false)
	{
		for (auto it = gp.personnels_.cbegin(); it != gp.personnels_.cend(); ++it)
		{
			it->second->afficher(os);
			os << '\n';
		}
		return os;
	}
	// TODO
	else
	{
		//TODO : Utiliser une boucle for ranged-based
	}
}

//TODO : à adapter au changement du type de l'attribut personnels_
const std::vector<std::shared_ptr<Personnel>>& GestionnairePersonnels::getPersonnels() const
{
	return personnels_;
}

/// TODO : Ajouter la méthode générique getPersonnelsAvecType()
// Elle retourne unordered_map de string et un pointeur vers le personnel
// La méthode parcours personnels_ et retourne un unordered_map de type désiré

// TODO : Ajouter la méthode getPersonnelsTriesSuivantSalaireAnnuel
// Elle trie le personnel de l’hôpital suivant le salaire annuel
// Elle retourne un vecteur de pair de string est shared_ptr<Pesonnel>
// On doit tout d’abord copier les éléments de la map personels_  dans un vecteur de std::pair<std::string, std::shared_ptr<Personnel>> 
// On utilise un algorithme de trie pour trier les éléments du vecteur. 
// Elle utilise le foncteur ComparateurSecondElementPaire.


//! Méthode qui retourne la liste des médecins de l'hôpital
//! \return la liste des médecins
std::vector<Medecin*> GestionnairePersonnels::getMedecins() const
{
	std::vector<Medecin*> medecins;
	for (const auto& personnel : personnels_) {
		Medecin* medecin = dynamic_cast<Medecin*>(personnel.get());
		if (medecin) {
			medecins.push_back(medecin);
		}
	}

	return medecins;
}

//! Méthode qui retourne la liste des médecins résidants de l'hôpital
//! \return la liste des médecins résidants
std::vector<MedecinResident*> GestionnairePersonnels::getMedecinsResidents() const
{
	std::vector<MedecinResident*> medecinsResidents;
	for (const auto& personnel : personnels_) {
		MedecinResident* medecinResident = dynamic_cast<MedecinResident*>(personnel.get());
		if (medecinResident) {
			medecinsResidents.push_back(medecinResident);
		}
	}

	return medecinsResidents;
}

//! Méthode qui retourne le nombre des personnels
//! \return le nombre de tous le pesonnels
size_t GestionnairePersonnels::getNbPersonnels() const
{
	return personnels_.size();
}

// TODO : à modifier
size_t GestionnairePersonnels::getNbMedecins() const
{
	return getMedecins().size();
}

// TODO : à modifier
size_t GestionnairePersonnels::getNbMedecinsResidents() const
{
	return getMedecinsResidents().size();
}


// TODO : Méthode à modifier
// Utiliser la fonction convertirStringDate implémentée dans utils.h  pour convertir dateAdhesion de string à tm
bool GestionnairePersonnels::lireLignePersonnel(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePersonnel;
	std::string nomPersonnel;
	std::string id;
	std::string dateAdhesion;

	std::string dateDeNaissance;
	std::string matricule;
	std::string etablissement;

	int indexSpecialite;

	if (stream >> indexTypePersonnel >> std::quoted(nomPersonnel) >> std::quoted(id))
	{
		switch (to_enum<GestionnairePersonnels::TypePersonnel, int>(indexTypePersonnel)) {
		case TypePersonnel::Medecin:
			stream >> indexSpecialite;
			return (*this) += std::make_shared<Medecin>(Medecin(nomPersonnel, id, to_enum<Medecin::Specialite, int>(indexSpecialite))).get();
		case TypePersonnel::MedecinResident:
			stream >> std::quoted(dateDeNaissance) >> std::quoted(matricule) >> std::quoted(etablissement) >> indexSpecialite;
			return (*this) += std::make_shared<MedecinResident>(MedecinResident(nomPersonnel, dateDeNaissance, matricule, etablissement, id, to_enum<Medecin::Specialite, int>(indexSpecialite))).get();
		default:
			assert(false); // ne devrait pas se passer avec le fichier fourni
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
