//! Implémentation de la classe GestionnairePatients qui permet de gérer les patients
//! \authors Didier Blach-Lafleche & Maude Tremblay
//! \date 14 juin 2020

#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

//! Constructeur par defaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients() : patients_(std::vector<std::shared_ptr<Patient>>())
{
}

//! Méthode qui cherche un patient avec son numéro d'assurance maladie
//! \param numeroAssuranceMaladie Numéro d'assurance maladie du patient
//! \return un pointeur vers le patient s'il est trouvé, sinon nullptr
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	std::vector<std::shared_ptr<Patient>>::iterator iter = std::find_if(patients_.begin(), patients_.end(), ComparateurEstEgalAvecId<Patient>(numeroAssuranceMaladie));
	if (iter != patients_.end())
	{
		return (*iter).get();
	}
	else { return nullptr; }
}

//! Méthode  qui permet de charger les informations des patients depuis un fichier
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succès
bool GestionnairePatients::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		patients_.clear();
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (!lireLignePatient(ligne))
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

//! Méthode qui ajoute un patient à l'objet GestionnairePatient
//! \param patient référence vers l'objet à jouter
//! \return true si le patient a été ajouté, false sinon
template<typename T>
bool GestionnairePatients::ajouterPatient(const T& patient)
{
	if (!chercherPatient(patient.getNumeroAssuranceMaladie())) {

		if (patients_.size() >= NB_PATIENT_MAX)
		{
			return false;
		}

		patients_.push_back(std::make_shared<T>(patient));

		return true;
	}
	return false;
}

//! Méthode qui supprime un patient
//! \param numeroAssMaladie Le numero d'assurance Maladie de type string du patient à supprimer
//! \return true si le patient a été supprimé, false sinon
bool GestionnairePatients::supprimerPatient(const std::string& numeroAssMaladie)
{
	size_t temp = patients_.size();
	(patients_.erase(std::remove_if(patients_.begin(),patients_.end(),ComparateurEstEgalAvecId<Patient>(numeroAssMaladie)), patients_.end()));
	if (patients_.size()!=temp)
	{
		return true;
	}
	else
	{
		return false;
	}

}


//! opérateur qui permet d'afficher la liste des patients
//! \param os Le stream dans lequel on veut afficher les informations
//! \param gestionnairePatients L'objet dont on veut afficher les information
//! \return le tream qui contient les informations
std::ostream& operator<<(std::ostream& os, const GestionnairePatients& gestionnairePatients)
{
	// Code fourni
	if constexpr (false)
	{
		for (auto it = gestionnairePatients.patients_.cbegin(); it != gestionnairePatients.patients_.cend(); ++it)
		{
			(*it)->afficher(os);
			os << '\n';
		}
		return os;
	}
	else
	{
		for (auto it : gestionnairePatients.patients_)
		{
			(it)->afficher(os);
			os << '\n';
		}
		return os;
	}
}

//! Méthode qui retourne tous les  patients
//! \return patients_ les patients
const std::vector<std::shared_ptr<Patient>>& GestionnairePatients::getPatients() const
{
	return patients_;
}

//! Méthode qui retourne la liste de tous les PatientEtudiant 
//! \return un vecteur de pointeur shared_ptr vers Patient
std::vector<std::shared_ptr<Patient>> GestionnairePatients::getPatientsEtudiants() const
{
	std::vector<std::shared_ptr<Patient>> patientsEtudiants;
	std::copy_if(patients_.begin(), patients_.end(), back_inserter(patientsEtudiants), ComparateurTypePatient<PatientEtudiant>());

	return patientsEtudiants;
}

//! Méthode qui retourne le nombre des patients dans la liste
//! \return Le nombre de patients dans la liste
size_t GestionnairePatients::getNbPatients() const
{
	return patients_.size();
}

//! Méthode qui retourne le nombre des patients étudiants dans la liste
//! \return Le nombre de patients étudiants dans la liste
size_t GestionnairePatients::getNbPatientsEtudiants() const
{
	return getPatientsEtudiants().size();
}

//! Méthode qui lit les attributs d'un patient
//! \param ligne  Le string qui contient les attributs
//! \return bool qui dit si la ligne a bien été lue
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePatient;
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;
	std::string dateAdhesion;

	std::string matricule;
	std::string etablissement;

	if (stream >> indexTypePatient >> std::quoted(nomPatient) >> std::quoted(anneeDeNaissance) >> std::quoted(numeroAssuranceMaladie) >> std::quoted(dateAdhesion))
	{
		switch (to_enum<GestionnairePatients::TypePatient, int>(indexTypePatient)) {
		case TypePatient::Patient:
			return ajouterPatient<Patient>(Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie,convertirStringDate(dateAdhesion)));
		case TypePatient::PatientEtudiant:
			stream >> std::quoted(matricule) >> std::quoted(etablissement);
			return ajouterPatient<PatientEtudiant>(PatientEtudiant(nomPatient, anneeDeNaissance, numeroAssuranceMaladie, convertirStringDate(dateAdhesion), matricule, etablissement));
		default:
			assert(false); // ne devrait pas se passer avec le fichier fourni
		}

		return true;
	}

	return false;
}
