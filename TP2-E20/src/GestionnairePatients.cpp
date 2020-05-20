// TODO: Faire l'entête de fichier

#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>

//! Constructeur par defaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients(){}

GestionnairePatients::GestionnairePatients(const GestionnairePatients& gestionnairePatient) {
	//for(Patient pat : gestPat)
	for (int i = 0; i < gestionnairePatient.getPatients().size(); i++) {
		patients_.push_back(gestionnairePatient.getPatients()[i]);
	}
}

GestionnairePatients& GestionnairePatients::operator=(const GestionnairePatients& gestionnairePatient) {
	if (this != &gestionnairePatient) {
		for (int i = 0; i < gestionnairePatient.getPatients().size(); i++) {
			patients_.push_back(gestionnairePatient.getPatients()[i]);
		}
	}
	return *this;
}


//! Méhode qui cherche un patient par son nom
//! \param nomPatient Le nom du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (std::shared_ptr<Patient> patient : patients_)
	{
		// À adapter au vecteur et pour l'opérateur==
		if (*patient == numeroAssuranceMaladie)
		{
			return &(*patient);  // this is weird
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
		for (int i =0; i < patients_.size(); i++){
			patients_.pop_back();
		}
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
bool GestionnairePatients::operator+=(const std::shared_ptr<Patient>& patient)
{
	if (patients_.size() >= NB_PATIENT_MAX){return false;}

	patients_.push_back(patient);
	return true;
}





// TODO : getPatients()  retourne une reference constante vers le vecteur patients_
std::vector<std::shared_ptr<Patient>>  GestionnairePatients::getPatients() const {
	return patients_;
};


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

	if (stream >> std::quoted(nomPatient) >> std::quoted(anneeDeNaissance) >> std::quoted(numeroAssuranceMaladie))
	{
		// Adapter cette méthode pour utiliser l'opérateur+=

		Patient pat(nomPatient, anneeDeNaissance, numeroAssuranceMaladie );
		std::shared_ptr<Patient> patient = std::make_shared<Patient>(pat);
		//const std::string& nomPatient, const std::string& anneeDeNaissance, const std::string& numeroAssuranceMaladie)

		*this += patient;
		return true;
	}
	return false;
}


// opérateur<< qui remplace afficher
//! Méthode pour afficher la liste des patients
//! \param stream Le stream dans lequel afficher
std::ostream& operator<<(std::ostream& stream, const GestionnairePatients& gestionnairePatients)
{
	for (int i = 0; i < gestionnairePatients.patients_.size(); i++)
	{
		stream << *(gestionnairePatients.patients_[i]);
		stream << '\n';
	}
}