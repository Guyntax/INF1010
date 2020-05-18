// TODO: Faire l'entête de fichier

#include "GestionnaireMedecins.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

constexpr size_t CAPACITE_MEDECINS_INITIALE = 2;
constexpr int MEDECIN_INEXSISTANT = -1;

//! Constructeur par defaut de la classe GestionnaireMedecins
GestionnaireMedecins::GestionnaireMedecins()
	: nbMedecins_(0)
	, capaciteMedecins_(CAPACITE_MEDECINS_INITIALE)
	, medecins_(std::make_unique<std::shared_ptr<Medecin>[]>(CAPACITE_MEDECINS_INITIALE))
{
}



//! Méthode qui cherche un medecin par son nom
//! \param nomMedecin Le nom du medecin à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le medecin n'existe pas dans la liste des medecin.
Medecin* GestionnaireMedecins::chercherMedecin(const std::string& numeroLicence)
{
	for (size_t i = 0; i < nbMedecins_; i++)
	{

		// Adapater la ligne ci-dessous en utilisant l'operateur == pour la comparaison
		if (medecins_[i]->getNumeroLicence() == numeroLicence)
		{
			// TODO retourner un pointeur vers le medecin 
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
		// Doit être adaptée pour vecteur
		nbMedecins_ = 0;
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


// TODO: Methode ajouterMedecin doit être remplacée par l'opérteur +=. il prend en paramètre une référence vers le medecin à ajouter
// Retourne true si l'opération d'ajout est réussie, false si non.

//! Méthode qui ajoute un médecin à la liste des patients
//! \param medecin Le medecin à ajouter
void GestionnaireMedecins::ajouterMedecin(std::shared_ptr<Medecin> medecin)
{
	constexpr unsigned int AUGMENTATION_NOMBRE_MEDECINS = 2;

	if (nbMedecins_ >= capaciteMedecins_)
	{
		// Creer nouveau tableau
		std::unique_ptr<std::shared_ptr<Medecin>[]> tableauTemporaire =
			std::make_unique<std::shared_ptr<Medecin>[]>(capaciteMedecins_ * AUGMENTATION_NOMBRE_MEDECINS);

		// Copier chaque élément vers le nouveau tableau
		for (std::size_t i = 0; i < nbMedecins_; i++)
		{
			tableauTemporaire[i] = medecins_[i];
		}

		medecins_ = move(tableauTemporaire);
		capaciteMedecins_ *= AUGMENTATION_NOMBRE_MEDECINS;
	}

	medecins_[nbMedecins_++] = medecin;
}

// TODO: Methode supprimerMedecin doit être remplacée par l'operteur -= Il prend en paramètre le numéro de licence 
// Retourne true si l'opération d'ajout est réussi, false si non.

//! Méthode  qui permet de supprimer un medecin
//! \param numeroLicence   numero de licence du medecin a supprimer
//! \return             Un bool qui indique si le medecin a été supprimé
bool GestionnaireMedecins::supprimerMedecin(const std::string& numeroLicence)
{
	int indexMedecin = trouverIndexMedecin(numeroLicence);

	if (indexMedecin != MEDECIN_INEXSISTANT)
	{
		medecins_[indexMedecin]->setEstActif(false);
		return true;
	}

	return false;

}

// TODO : La methode afficher doit être remplacée par l’opérateur << 
//! Méthode pour afficher la liste des medecins
//! \param stream Le stream dans lequel afficher
void GestionnaireMedecins::afficher(std::ostream& stream) const
{
	for (size_t i = 0; i < nbMedecins_; i++)
	{
		medecins_[i]->afficher(stream);
		stream << '\n';
	}
}


//! Méthode qui retourne le nombre des medecins dans la liste
//! \return Le nombre de medecins dans la liste
size_t GestionnaireMedecins::getNbMedecins() const
{
	return nbMedecins_;
}

// TODO : getMedecins() retourne une reference constante vers le vecteur medecins_

size_t GestionnaireMedecins::getCapaciteMedecins() const
{

	return capaciteMedecins_;
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
		// Adapter cette méthode pour utiliser l'opérateur+=
		ajouterMedecin(std::make_unique<Medecin>(nomMedecin, numeroLicence, to_enum<Medecin::Specialite, int>(indexSpecialite)));
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
	for (std::size_t i = 0; i < nbMedecins_; i++)
	{
		if (medecins_[i]->getNumeroLicence() == numeroLicence)
		{
			return static_cast<int>(i);
		}
	}
	return MEDECIN_INEXSISTANT;
}
