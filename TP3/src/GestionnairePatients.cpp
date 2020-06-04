//! Implémentation de la classe GestionnairePatients qui permet de gérer les patients de l'hôpital.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

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

//! Méhode qui cherche un patient par son numero d'assurance maladie
//! \param numeroAssuranceMaladie Le numero d'assurance maladie Le numero d'assurance maladie du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (const auto& patient : patients_)
	{
		if (*patient == numeroAssuranceMaladie)
		{
			return patient.get(); // retourne un pointeur vers le patient trouvé
		}
	}
	return nullptr; // retourne un ptr null i le patient n'est pas trouvé
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
			if (!lireLignePatient(ligne)) // Lit chaque ligne et retourne false si il y a un probleme
			{
				return false;
			}
		}
		return true; // retourne true si toutes les ignes on été lues sans problemes
	}
	std::cerr << "Le fichier " << nomFichier
		<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";

	return false; // retourne false si le ficher ne s'ouvre pas
}

//! Operateur qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return        Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePatients::operator+=(Patient* patient)
{
	if (patient && !chercherPatient(patient->getNumeroAssuranceMaladie())) {

		if (patients_.size() >= NB_PATIENT_MAX) // on verifie si il y a de la place
		{
			return false; // return false si il ny a pas de place
		}
		// Vérifier si Patient est un PatientEtudiant ou un patient normal, pour l'ajouter correctement
		if (dynamic_cast<PatientEtudiant*>(patient)) {
			patients_.push_back(std::make_shared<PatientEtudiant>(*dynamic_cast<PatientEtudiant*>(patient))); 
		}
		else if (dynamic_cast<Patient*>(patient)) {
			patients_.push_back(std::make_shared<Patient>(*patient)); 
		}
		else {
			assert(false);
		}
		return true; // return true si il ya de la place pour la patient
	}
	return false; // retourne false si le patient existe deja dans le gesttionnaire
}

//! opérateur qui affiche les patients
//! \param os Le stream dans lequel afficher
//! \param gestionnairePatients le gestionnaire de patient que l'on veut afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePatients& gestionnairePatients)
{
	for (const auto& patient : gestionnairePatients.patients_)
	{
		patient->afficher(os);
		os << '\n';
	}
	return os; // retourne le ostream par référence
}


//! Méthode qui retourne tous les  patients

const std::vector<std::shared_ptr<Patient>>& GestionnairePatients::getPatients() const
{
	return patients_; //! \return patients_ les patients
}


//! Méthode qui retourne tous les  patients étudiants
//! \return un vecteur de PatientEtudiant*
std::vector<PatientEtudiant*> GestionnairePatients::getPatientsEtudiants() const {
	std::vector<PatientEtudiant*> vecteur ;
	for (const auto& patient : patients_) {
		if (dynamic_cast<PatientEtudiant*>(patient.get())) {
			vecteur.push_back(dynamic_cast<PatientEtudiant*>(patient.get())); 
		}
	}
	return  vecteur; // retourne le vecteur de patientEtudiant par valeur
}


//! Méthode qui retourne le nombre des patients dans la liste
//! \return Le nombre de patients dans la liste
size_t GestionnairePatients::getNbPatients() const{
	return patients_.size();
}

// Done : Méthode getNbPatientsEtudiants
// Retourner le nombre de patients étudiants
size_t GestionnairePatients::getNbPatientsEtudiants() const {
	return getPatientsEtudiants().size();
}


//! Méthode qui lit les attributs d'un patient
//! \param ligne  Le string qui contient les attributs
//! \return bool qui dit si la ligne a bien été lue
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePatient; // Indique le type de patient. 0 : Patient , 1 : PatientEtudiant (voir l'enum TypePatient)
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;

	std::string matricule;
	std::string etablissement;

	if (stream >> indexTypePatient >> std::quoted(nomPatient) >> std::quoted(anneeDeNaissance) >> std::quoted(numeroAssuranceMaladie)){ 
		
		GestionnairePatients::TypePatient typePatient = to_enum<GestionnairePatients::TypePatient, int>(indexTypePatient);
		
		switch (typePatient) {
		case GestionnairePatients::TypePatient::Patient : 
			// Ajoute le pointer nouvelment créé et retoune true, si c'est un succès
			return (*this) += std::make_shared<Patient>(Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie)).get();

		case GestionnairePatients::TypePatient::PatientEtudiant : 
			stream >> std::quoted(matricule) >> std::quoted(etablissement);
			// Ajoute le pointer nouvelment créé et retoune true, si c'est un succès
			return (*this) += std::make_shared<PatientEtudiant>(PatientEtudiant(nomPatient, anneeDeNaissance, numeroAssuranceMaladie, matricule, etablissement)).get();
		
		default :
			assert(false); // ne devrait pas passer avec le fichier fourni
		}
	}
	return false; // retourne false si on ne peut pas lire à partir du stream
}
