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
	
//! Méthode qui permet de chercher un personnel avec son id
//! \param id	ID du personnel
//! \return pointeur vers le personnel
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


//! Méthode qui permet d'obtenir la liste du personnel de l'hôpital
//! \return             Une unordered_map de share_ptr de personnels dont les clés sont leur id
const std::unordered_map<std::string, std::shared_ptr<Personnel>>& GestionnairePersonnels::getPersonnels() const
{
	return personnels_;
}

//! Méthode qui permet d'obtenir la liste de personnel de l'hôpital trié suivant le salaire annuel
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

//! Méthode qui permet d'obtenir le nombre de médecins de l'hôpital
//! \return le nombre de Medecins
size_t GestionnairePersonnels::getNbMedecins() const
{
	return getPersonnelsAvecType<Medecin>().size();
}

//! Méthode qui permet d'obtenir le nombre de médecins résidents de l'hôpital
//! \return le nombre de Medecins Résidents
size_t GestionnairePersonnels::getNbMedecinsResidents() const
{
	return getPersonnelsAvecType<MedecinResident>().size();
}


//! Méthode qui lit les attributs d'un patient
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