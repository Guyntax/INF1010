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



//! Operateur qui permet d'afficher les informations des personnels 
//! \param os					   Le stream dans lequel afficher
//! \param gestionnairePersonnels  Le gestionnaire personnels à afficher
//! \return						   Le stream dans lequel afficher

std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePersonnels)
{
	for (auto& it : gestionnairePersonnels.personnels_) {
		it.second->afficher(os);
		os << '\n';
	}
	return os;
}


//! \return             Une unordered_map de share_ptr de personnels dont les clés sont leur id
const std::unordered_map<std::string, std::shared_ptr<Personnel>>& GestionnairePersonnels::getPersonnels() const
{
	return personnels_;
}


// Elle trie le personnel de l’hôpital suivant le salaire annuel
// Elle retourne un vecteur de pair de string est shared_ptr<Pesonnel>
// On doit tout d’abord copier les éléments de la map personels_  dans un vecteur de std::pair<std::string, std::shared_ptr<Personnel>> 
// On utilise un algorithme de trie pour trier les éléments du vecteur. 
// Elle utilise le foncteur ComparateurSecondElementPaire.
//! \return				Le vecteur de pairs contenant l'identifiant et le shared_ptr du personnel
std::vector<std::pair<std::string, std::shared_ptr<Personnel>>> GestionnairePersonnels::getPersonnelsTriesSuivantSalaireAnnuel() const {
	std::vector<std::pair<std::string, std::shared_ptr<Personnel>>> vecteur;
	std::copy(personnels_.begin(), personnels_.end(), back_inserter(vecteur));
	std::sort(vecteur.begin(), vecteur.end(), ComparateurSecondElementPaire<std::string, std::shared_ptr<Personnel>>());
	return vecteur;
}

//! Méthode qui retourne le nombre des personnels
//! \return le nombre de tous le pesonnels
size_t GestionnairePersonnels::getNbPersonnels() const
{
	return personnels_.size();
}

//! \return le nombre de Medecins
size_t GestionnairePersonnels::getNbMedecins() const
{
	return getPersonnelsAvecType<Medecin>().size();
}

//! \return le nombre de Medecins Résidents
size_t GestionnairePersonnels::getNbMedecinsResidents() const
{
	return getPersonnelsAvecType<MedecinResident>().size();
}


// Utiliser la fonction convertirStringDate implémentée dans utils.h  pour convertir dateAdhesion de string à tm
//! \param ligne		La ligne du fichier à lire à lire
//! \return				Un bool qui indique si la ligne a été lue avec succès
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
		// créé le personnel selon s'il est un medecin ou medecinResident
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