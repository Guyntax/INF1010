// TODO: Faire l'entête de fichier

#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

//! Constructeur par defaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients()
	: nbPatients_(0)
{
}


//! Méhode qui cherche un patient par son nom
//! \param nomPatient Le nom du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (Patient patient : patients_)
	{
		// À adapter au vecteur et pour l'opérateur==
		if (patient.getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			return &patient;
		}
	}

	return nullptr;
}

//! Méthode  qui permet de charger les informations des patients depuis un fichier
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succès
bool GestionnairePatients::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		// À adapter au vecteur
		nbPatients_ = 0;
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (lireLignePatient(ligne) == false)
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

// TODO: Methode ajouterPatientdoit être remplacée par l'operteur +=. il prend en paramètre une référence vers le patient à ajouter
// Retourne true si l'opération d'ajout est réussi, false si non.

//! Méthode qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePatients::ajouterPatient(const Patient& patient)
{
	if (nbPatients_ >= NB_PATIENT_MAX)
	{
		return false;
	}

	patients_[nbPatients_++] = patient;
	return true;
}

// TODO : La methode afficher  doit être remplacée L’opérateur << 
//! Méthode pour afficher la liste des patients
//! \param stream Le stream dans lequel afficher
void GestionnairePatients::afficher(std::ostream& stream) const
{
	for (size_t i = 0; i < nbPatients_; i++)
	{
		patients_[i].afficher(stream);
		stream << '\n';
	}
}

//! Méthode qui retourne le nombre des patients dans la liste
//! \return Le nombre de patients dans la liste
size_t GestionnairePatients::getNbPatients() const
{
	return nbPatients_;
}

// TODO : getPatients()  retourne une reference constante vers le vecteur patients_

//! Méthode qui lit les attributs d'un patient
//! \param ligne  Le string qui contient les attributs
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;


	// Pour extraire ce qui se trouve entre "" dans un stream,
	// il faut faire stream >> quoted(variable)

	if (stream >> quoted(nomPatient) >> quoted(anneeDeNaissance) >> quoted(numeroAssuranceMaladie))
	{
		// Adapter cette méthode pour utiliser l'opérateur+=
		return ajouterPatient(Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie));
	}
	return false;
}
