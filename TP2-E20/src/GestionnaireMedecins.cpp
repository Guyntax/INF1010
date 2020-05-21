//! Définition de la classe GestionnaireMedecins qui permet la gestion des médecins de l'hôpital
//! \authors Didier Blach Laflèche & Maude Tremblay
//! \date 20 Mai 2020

#include "GestionnaireMedecins.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

constexpr int MEDECIN_INEXSISTANT = -1;

//! Constructeur par defaut de la classe GestionnaireMedecins
GestionnaireMedecins::GestionnaireMedecins():
	medecins_(std::vector<std::shared_ptr<Medecin>>())
{
}

//! Constructeur de copie de la classe GestionnaireMedecins
GestionnaireMedecins::GestionnaireMedecins(const GestionnaireMedecins& gestionnaireMedecins) 
{

	for (int i = 0; i < gestionnaireMedecins.getMedecins().size(); i++) {
		medecins_.push_back(std::make_shared<Medecin>(*gestionnaireMedecins.getMedecins()[i]));
	}
}

//! Opérateur d'affectation
GestionnaireMedecins& GestionnaireMedecins::operator=(const GestionnaireMedecins& gestionnaireMedecins) {
	if (this != &gestionnaireMedecins) {
		for (int i = 0; i < gestionnaireMedecins.medecins_.size(); i++)
		{
			operator+=(*(gestionnaireMedecins.medecins_[i]));
		}
	}
	return *this;
}

//! Méthode qui cherche un medecin par son nom
//! \param nomMedecin Le nom du medecin à chercher
//! \return Un pointeur vers le medecin. Le pointeur est nullptr si le medecin n'existe pas dans la liste des medecin.
Medecin* GestionnaireMedecins::chercherMedecin(const std::string& numeroLicence) const
{
	for (size_t i = 0; i < medecins_.size(); i++)
	{
		if (medecins_[i]->getNumeroLicence() == numeroLicence)
		{
			return medecins_[i].get();
		}
	}

	return nullptr;
}


//! Méthode  qui permet de charger les informations des medecins depuis un fichier
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succes
bool GestionnaireMedecins::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		int size = medecins_.size(); // necessaire, car patients_.size() change dans la boucle
		for (int i = 0; i < size; i++) {
			medecins_.pop_back();
		}
		// Doit être adaptée pour vecteur
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (lireLigneMedecin(ligne) == false)
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


//! Surcharge de l'opérateur += : opérateur qui ajoute un médecin à la liste des médecins
//! \param medecin Le medecin à ajouter
//! \return true si l'opération d'ajout est réussie, false sinon.
bool GestionnaireMedecins::operator+= (Medecin medecin)
{
	int nbMedecinInit = medecins_.size();
	medecins_.push_back(std::make_shared<Medecin>(medecin));
		if ((nbMedecinInit + 1) == medecins_.size())
		{
			return true;
		}
		else
		{
			return false;
		}
	
}

// TODO: Methode supprimerMedecin doit être remplacée par l'operteur -= Il prend en paramètre le numéro de licence 
// Retourne true si l'opération d'ajout est réussi, false si non.

//! Surcharge de l'opérateur -= : opérateur qui permet de supprimer un medecin
//! \param numeroLicence   numero de licence du medecin a supprimer
//! \return             Un bool qui indique si le medecin a été supprimé
bool GestionnaireMedecins::operator-=(const std::string& numeroLicence)
{
	int indexMedecin = trouverIndexMedecin(numeroLicence);

	if (indexMedecin != MEDECIN_INEXSISTANT)
	{
		medecins_[indexMedecin]->setEstActif(false);
		return true;
	}

	return false;

}


//! Surcharge de l'opérateur << : opérateur pour afficher la liste des medecins
//! \param stream Le stream dans lequel afficher
//! \return stream Le stream dans lequel les informations sont affichées
std::ostream& operator<<(std::ostream& stream, const GestionnaireMedecins& gestMed)
{
	for (size_t i = 0; i < gestMed.medecins_.size(); i++)
	{
		stream << *(gestMed.medecins_[i])<< '\n';
	}
	return stream;
}


//! Méthode qui retourne le nombre des medecins dans la liste
//! \return Le nombre de medecins dans la liste
size_t GestionnaireMedecins::getNbMedecins() const
{
	return medecins_.size();
}

//! Méthode qui retourne vecteur medecins_
//! \return Vecteur medecins_
const std::vector<std::shared_ptr<Medecin>>& GestionnaireMedecins::getMedecins() const
{
	return medecins_;
}

//! Méthode qui retourne la capacité du vecteur medecins_
//! \return Capacité du vecteur medecins_
size_t GestionnaireMedecins::getCapaciteMedecins() const
{
	return medecins_.capacity();
}

//! Méthode qui lit les attributs d'un medecin
//! \param ligne  Le string qui contient les attributs
bool GestionnaireMedecins::lireLigneMedecin(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomMedecin;
	std::string numeroLicence;
	int indexSpecialite;


	// Pour extraire ce qui se trouve entre "" dans un stream,
	// il faut faire stream >> quoted(variable)

	if (stream >> std::quoted(nomMedecin) >> std::quoted(numeroLicence) >> indexSpecialite)
	{
		operator+=(Medecin(nomMedecin, numeroLicence, to_enum<Medecin::Specialite, int>(indexSpecialite)));
		return true;
	}

	return false;
}

//! Méthode  qui permet de trouver l'index un medecin dans la liste des medecins
//! \param numeroLicence   numero de licence du medecin
//! \return             int bool qui indique l'index du medecin et MEDECIN_INEXSISTANT si le medecin est inexistant
int GestionnaireMedecins::trouverIndexMedecin(const std::string& numeroLicence)
{
	// À Adapter pour vecteur et l'utilisation l'opérateur == 
	for (std::size_t i = 0; i < medecins_.size(); i++)
	{
		if (*(medecins_[i]) == numeroLicence)
		{
			return static_cast<int>(i);
		}
	}
	return MEDECIN_INEXSISTANT;
}
