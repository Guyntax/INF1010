//! Implémentation de la classe GestionnairePersonnels qui permet de gérer les personnels de l'hôpital
//! \authors Didier Blach-Lafleche & Maude Tremblay
//! \date 14 juin 2020

#include "GestionnairePersonnels.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include "typesafe_enum.h"
#include "Foncteurs.h"

constexpr int PERSONNEL_INEXSISTANT = -1;

//DONE : Modifier cette méthode		
// Cette méthode doit utiliser la fonction find
// Consulter l'énoncer pour cette méthode pour voir plus d'explication
// Le nombre des lignes de code maximale est 4 lignes (sans compter la signature, les lignes vides et les lignes avec accolades)
Personnel* GestionnairePersonnels::chercherPersonnel(const std::string& id) const
{
	std::unordered_map<std::string, std::shared_ptr<Personnel>>::const_iterator iterator = personnels_.find(id);
	if (iterator != personnels_.end()){
		return iterator->second.get();
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

// DONE: Remplacer l'opérateur par la méthode générique ajouterPersonnel
// La méthode prend une référence vers l'objet à ajouter
// L'implémentation doit être modifié aussi
// Le nombre des lignes de code maximale est 3 lignes (sans compter la signature, les lignes vides et les lignes avec accolades)
template <typename T>
bool GestionnairePersonnels::ajouterPersonnel(const T& objet)
{
	std::shared_ptr<T> ptr = std::make_shared<T>(objet);
	if (dynamic_cast<Personnel*>(ptr.get()) && !chercherPersonnel(objet.getId()) ) {
		personnels_[objet.getId()] = ptr;
		return true;
	}
	return false;
}

// DONE: Remplacer l'opérateur par la méthode supprimerPesonnel
// La méthode prend un string qui est l'id de personnel à supprimer
template <typename T>
bool GestionnairePersonnels::supprimerPesonnel(std::string id){
	//TODO : utiliser la méthode chercherPersonnel
	if (chercherPersonnel(id)){
		personnels_[id]->setEstActif(false);
		return true;
	}
	return false;
}

//! Operateur qui permet d'afficher les informations des personnels 
//! \param os					   Le stream dans lequel afficher
//! \param gestionnairePersonnels  Le gestionnaire personnels à afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePersonnels)
{
	// Code fourni A ENELVER
	if constexpr (false)
	{
		for (auto it = gestionnairePersonnels.personnels_.cbegin(); it != gestionnairePersonnels.personnels_.cend(); ++it)
		{
			it->second->afficher(os);
			os << '\n';
		}
		return os;
	}
	// TODO: ENELVER CE QUI PRECEDE
	else
	{
		//DONE : Utiliser une boucle for ranged-based
		for (auto& it : gestionnairePersonnels.personnels_) {
			it.second->afficher(os);
			os << '\n';
		}
		return os;
	}
}

//DONE : à adapter au changement du type de l'attribut personnels_
const std::unordered_map<std::string, std::shared_ptr<Personnel>>& GestionnairePersonnels::getPersonnels() const
{
	return personnels_;
}

/// TODO : Ajouter la méthode générique getPersonnelsAvecType()
// Elle retourne unordered_map de string et un pointeur vers le personnel
// La méthode parcours personnels_ et retourne un unordered_map de type désiré
template <typename T>
std::unordered_map<std::string, T*> GestionnairePersonnels::getPersonnelsAvecType() const {
	std::unordered_map<std::string, T*> map;
	for (auto& element : personnels_) {//gestionnairePersonnels.personnels_
		T* casted_element = (dynamic_cast<T*>(element.second.get()));
		if (casted_element) {
			map.emplace(casted_element->getId(), casted_element);
		}
	}
	return map;
}

// TODO : Ajouter la méthode getPersonnelsTriesSuivantSalaireAnnuel
// Elle trie le personnel de l’hôpital suivant le salaire annuel
// Elle retourne un vecteur de pair de string est shared_ptr<Pesonnel>
// On doit tout d’abord copier les éléments de la map personels_  dans un vecteur de std::pair<std::string, std::shared_ptr<Personnel>> 
// On utilise un algorithme de trie pour trier les éléments du vecteur. 
// Elle utilise le foncteur ComparateurSecondElementPaire.
std::vector<std::pair<std::string, std::shared_ptr<Personnel>>> GestionnairePersonnels::getPersonnelsTriesSuivantSalaireAnnuel() const {
	std::vector<std::pair<std::string, std::shared_ptr<Personnel>>> vecteur;
	std::copy(personnels_.begin(), personnels_.end(), back_inserter(vecteur));

	std::sort(vecteur.begin(), vecteur.end(), ComparateurSecondElementPaire<std::string, std::shared_ptr<Personnel>>());
	return vecteur;
}

/*
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
*/

//! Méthode qui retourne le nombre des personnels
//! \return le nombre de tous le pesonnels
size_t GestionnairePersonnels::getNbPersonnels() const
{
	return personnels_.size();
}

// DONE : à modifier

size_t GestionnairePersonnels::getNbMedecins() const
{
	return getPersonnelsAvecType<Medecin>().size();
}

// DONE : à modifier
size_t GestionnairePersonnels::getNbMedecinsResidents() const
{
	return getPersonnelsAvecType<MedecinResident>().size();
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

	if (stream >> indexTypePersonnel >> std::quoted(nomPersonnel) >> std::quoted(id) >> std::quoted(dateAdhesion))
	{
		switch (to_enum<GestionnairePersonnels::TypePersonnel, int>(indexTypePersonnel)) {
		case TypePersonnel::Medecin:
			stream >> indexSpecialite;
			return ajouterPersonnel(Medecin(nomPersonnel, id, to_enum<Medecin::Specialite, int>(indexSpecialite), convertirStringDate(dateAdhesion)));
		case TypePersonnel::MedecinResident:
			stream >> std::quoted(dateDeNaissance) >> std::quoted(matricule) >> std::quoted(etablissement) >> indexSpecialite;
			return ajouterPersonnel(MedecinResident(nomPersonnel, dateDeNaissance, matricule, etablissement, id, to_enum<Medecin::Specialite, int>(indexSpecialite), convertirStringDate(dateAdhesion)));
		default:
			assert(false); // ne devrait pas se passer avec le fichier fourni
		}
	}

	return false;
}

/*
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
*/