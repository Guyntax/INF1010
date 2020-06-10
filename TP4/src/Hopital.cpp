//TODO Entête du fichier

#include "Hopital.h"
#include "ConsultationEnligne.h"
#include "ConsultationPhysique.h"
#include "typesafe_enum.h"
#include "assert.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <numeric>

//! Constructeur par paramètre  de la classe Hopital
//! \param nom      Nom de l'hopital
//! \param adresse  Adresse de l'hopital
Hopital::Hopital(const std::string& nom, const std::string& adresse) :nom_(nom), adresse_(adresse)
{
}

// DONE: A mofidier pour qu'elle prenne aussi le nom du fichier des consulations.
// Elle doit charger les consultations en faisant appel à la fonction chargerDepuisFichierConsultation 
bool Hopital::chargerBaseDeDonnees(const std::string& nomFichierPersonnels, const std::string& nomFichierPatients, const std::string& nomFichierConsultations)
{
	return gestionnairePersonnels_.chargerDepuisFichier(nomFichierPersonnels)
		&& gestionnairePatients_.chargerDepuisFichier(nomFichierPatients) && chargerDepuisFichierConsultation(nomFichierConsultations);
}

//! Méthode  qui permet de charger les informations des consultations
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succes
bool Hopital::chargerDepuisFichierConsultation(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		consultations_.clear();
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (!lireLigneConsultation(ligne))
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

// DONE : Ajouter la méthode getAncienneteMoyenneDesPersonnels 
// Elle retourne la moyenne de l'ancienneté des personnels de type double
// Elle utilise la fonction accumulate de la STL et le foncteur AccumulateurPeriodePersonnel
// Le nombre des lignes de code maximale est 1 ligne (sans compter la signature, les lignes vides et les lignes avec accolades)
double Hopital::getAncienneteMoyenneDesPersonnels()
{
	return (std::accumulate((gestionnairePersonnels_.GestionnairePersonnels::getPersonnels()).begin(), (gestionnairePersonnels_.GestionnairePersonnels::getPersonnels()).end(),0,AccumulateurPeriodePersonnel(0))/(gestionnairePersonnels_.GestionnairePersonnels::getPersonnels()).size());
}


// DONE : Ajouter la méthode getCosultationsEntreDates
// Deux paramètres : références constantes vers des objets de type tm
// Elle retourne un vecteur de shared_ptr vers Consultation
// Elle utilise la fonction copy_if, back_inserter et le foncteur EstDansIntervalleDatesConsultation.
std::vector<std::shared_ptr<Consultation>> Hopital::getConsultationsEntreDates(tm& date1, tm& date2)
{
	std::vector<std::shared_ptr<Consultation>> consult;
	std::copy_if(consultations_.begin(), consultations_.end(), back_inserter(consult), EstDansIntervalleDatesConsultation(date1,date2) );
	return consult;
}


// DONE: Remplacer l'opérateur par la méthode générique ajouterConsultation
// La méthode prend une référence vers l'objet à ajouter
// L'implémentation de la méthode à modifier pour s'adapter à la fonction générique
template <typename consult>
bool Hopital::ajouterConsultation(consult& consultation)
{
	Medecin* medecin = dynamic_cast<Medecin*>(gestionnairePersonnels_.chercherPersonnel(consultation.getMedecin()->getId()));
	if (medecin && medecin->getEstActif())
	{
		Patient* patient = gestionnairePatients_.chercherPatient(consultation.getPatient()->getNumeroAssuranceMaladie());
		if (!patient)
		{
			return false;
		}

		consultations_.push_back(std::make_shared<consult>(consultation));

		Patient* patientDuMedecin = medecin->chercherPatient(patient->getNumeroAssuranceMaladie());
		if (!patientDuMedecin)
		{
			*medecin += patient;
		}
		medecin->incrementNombreConsultations();

		return true;
	}

	return false;
}

//! Méthode qui retourne le nom de l'hopital
//! \return nom_ le nom de l'hopital 
const std::string& Hopital::getNom() const
{
	return nom_;
}

//! Méthode qui retourne l'adresse de l'hopital
//! \return adresse_ l'adresse de l'hopital 
const std::string& Hopital::getAdresse() const
{
	return adresse_;
}

//! Méthode qui retourne le gestionnaire du personnels
//! \return gestionnairePersonnels_ gestionnaire du personnels
GestionnairePersonnels& Hopital::getGestionnairePersonnels()
{
	return gestionnairePersonnels_;
}

//! Méthode qui retourne le gestionnaire des patients
//! \return gestionnaire des patients
GestionnairePatients& Hopital::getGestionnairePatients()
{
	return gestionnairePatients_;
}

//! Méthode qui retourne les consultaions de l'hopital
//! \return consultations_ les consultations
const std::vector<std::shared_ptr<Consultation>>& Hopital::getConsultations() const
{
	return consultations_;
}

//! Méthode qui permet de mettre à jour le nom de l'hopital
//! \Param nom Le nom de l'hopital
void Hopital::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui permet de mettre à jour l'adresse de l'hopital
//! \Param adresse  l'adresse de l'hopital
void Hopital::setAdresse(const std::string& adresse)
{
	adresse_ = adresse;
}

//! Méthode qui lit les attributs d'une consulation
//! \param ligne  Le string qui contient les attributs
//! \return le status de l'opération si elle s'est bien passée
bool Hopital::lireLigneConsultation(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypeConsultation;
	std::string idMedecin;
	std::string idPatient;
	std::string dateConsultation;

	if (stream >> indexTypeConsultation >> std::quoted(idMedecin) >> std::quoted(idPatient) >> std::quoted(dateConsultation))
	{
		Medecin* medecin = dynamic_cast<Medecin*>(gestionnairePersonnels_.chercherPersonnel(idMedecin));
		Patient* patient = gestionnairePatients_.chercherPatient(idPatient);

		if (medecin && patient) {
			TypeConsultation typeConsultation = to_enum<Hopital::TypeConsultation, int>(indexTypeConsultation);
			if (typeConsultation == TypeConsultation::ConsultationEnLigne)
			{
				ConsultationEnligne consultation = ConsultationEnligne(*medecin, *patient, dateConsultation);

				return ajouterConsultation(consultation);
			}
			else if (typeConsultation == TypeConsultation::ConsultationPhysique)
			{
				ConsultationPhysique consultation = ConsultationPhysique(*medecin, *patient, dateConsultation);

				return ajouterConsultation(consultation);
			}
			else
			{
				assert(false); // ne devrait pas se passer avec le fichier fourni
			}
		}
		else {
			return false;
		}
	}

	return false;
}