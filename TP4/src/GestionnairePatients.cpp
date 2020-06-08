//TODO Entête du fichier

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

//TODO : Modifier cette méthode 
// Cette méthode doit utiliserla fonction find_if et le foncteur ComparateurEstEgalAvecId.
// Consulter l'énoncer pour cette méthode pour voir plus d'explication
// Le nombre des lignes de code maximale est 4 lignes (sans compter la signature, les lignes vides et les lignes avec accolades)
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (auto& patient : patients_)
	{
		if (*patient == numeroAssuranceMaladie)
		{
			return patient.get();
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

// TODO: Remplacer l'opérateur par la méthode générique ajouterPatient
// La méthode prend une référence vers l'objet à jouter
// L'implémentation doit être modifié aussi
// Le nombre des lignes de code maximale est 6 lignes (sans compter la signature, les lignes vides et les lignes avec accolades)
bool GestionnairePatients::operator+=(Patient* patient)
{
	if (patient && !chercherPatient(patient->getNumeroAssuranceMaladie())) {

		if (patients_.size() >= NB_PATIENT_MAX)
		{
			return false;
		}

		if (dynamic_cast<PatientEtudiant*>(patient)) {
			patients_.push_back(std::make_shared<PatientEtudiant>(*dynamic_cast<PatientEtudiant*>(patient)));
		}
		else {
			patients_.push_back(std::make_shared<Patient>(*patient));
		}

		return true;
	}
	return false;
}

// TODO : Ajouter la méthode supprimerPatient
// Les paramètres : numero d'assurance Maladie de type string patient à supprimer
// Retourn un booléan
//Elle utilise les fonctions erase, remove_if et le foncteur ComparateurEstEgalAvecId.



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
	// TODO
	else
	{
		//TODO : utiliser une boucle for range-based
	}
}

//! Méthode qui retourne tous les  patients
//! \return patients_ les patients
const std::vector<std::shared_ptr<Patient>>& GestionnairePatients::getPatients() const
{
	return patients_;
}

// TODO Modifier cette méthode.
// Elle retourne un vecteur de pointeur shared_ptr vers Patient
// Elle utilise copy_if, back_inserter et le foncteur ComparateurTypePatient
// Le nombre des lignes de code maximale est 3 lignes (sans compter la signature, les lignes vides et les lignes avec accolades)
std::vector<PatientEtudiant*> GestionnairePatients::getPatientsEtudiants() const
{
	std::vector<PatientEtudiant*> patientsEtudiants;
	for (const auto& patient : patients_) 
	{
		PatientEtudiant* patientEtudiant = dynamic_cast<PatientEtudiant*>(patient.get());
		if (patientEtudiant) 
		{
			patientsEtudiants.push_back(patientEtudiant);
		}
	}

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

// TODO : Méthode à modifier
// Utiliser la fonction convertirStringDate implémentée dans utils.h  pour convertir dateAdhesion de string à tm
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

	if (stream >> indexTypePatient >> std::quoted(nomPatient) >> std::quoted(anneeDeNaissance) >> std::quoted(numeroAssuranceMaladie))
	{
		switch (to_enum<GestionnairePatients::TypePatient, int>(indexTypePatient)) {
		case TypePatient::Patient:
			return (*this) += std::make_shared<Patient>(Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie)).get();
		case TypePatient::PatientEtudiant:
			stream >> std::quoted(matricule) >> std::quoted(etablissement);
			return (*this) += std::make_shared<PatientEtudiant>(PatientEtudiant(nomPatient, anneeDeNaissance, numeroAssuranceMaladie, matricule, etablissement)).get();
		default:
			assert(false); // ne devrait pas se passer avec le fichier fourni
		}

		return true;
	}

	return false;
}
