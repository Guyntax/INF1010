//! Impléèmentation de la classe GestionnairePatients qui permet la gestion des patients de l'hôpital
//! \authors Didier Blach Laflèche & Maude Tremblay
//! \date 21 Mai 2020

#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

//! Constructeur par defaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients(){}

//! Constructeur de copie de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients(const GestionnairePatients& gestionnairePatient) {
	for (int i = 0; i < gestionnairePatient.getPatients().size(); i++) {
		patients_.push_back(std::make_shared<Patient> (*gestionnairePatient.getPatients()[i]) );
	}
}

//! Opérateur d'affectation
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
		int size = patients_.size(); // necesaire, car patients_.size() change dans la boucle
		for (int i =0; i < size; i++){
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


//! Surcharge de l'opérateur += : opérateur qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePatients::operator+=(const Patient& patient)
{

	if (!chercherPatient(patient.getNumeroAssuranceMaladie()) && (patients_.size() < NB_PATIENT_MAX)) {
		patients_.push_back(std::make_shared<Patient>(patient));
		return true;
	}
	return false;
}

//! Surcharge de l'opérateur<< : opérateur qui affiche la liste des patients
//! \param stream Le stream dans lequel afficher
//! \return le stream qui contient les informations
std::ostream& operator<<(std::ostream& stream, const GestionnairePatients& gestionnairePatients)
{
	for (int i = 0; i < gestionnairePatients.patients_.size(); i++)
	{
		stream << *(gestionnairePatients.patients_[i]);
		stream << '\n';
	}
	return stream;
}

//! Méthode qui retourne une reference constante vers le vecteur patients_
//! \return une reference constante vers le vecteur patients_
std::vector<std::shared_ptr<Patient>>  GestionnairePatients::getPatients() const {
	return patients_;
};

//! Méthode qui retourne le nombre de patients
//! \return le nombre de patients
int GestionnairePatients::getNbPatients()const {
	return patients_.size();
};



//! Méthode qui lit les attributs d'un patient
//! \param ligne  Le string qui contient les attributs
//! \return true si la ligne a bien été lue, sinon false
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
		Patient patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie );

		*this += patient;
		return true;
	}
	return false;
}


