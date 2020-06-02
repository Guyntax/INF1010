//! Implémentation de la classe Medecin qui hérite de Personnel. Cette classe représente un médecin qui exerce dans l'hôpital.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#include <iostream>
#include "Medecin.h"
#include "typesafe_enum.h"

constexpr int PATIENT_INEXSISTANT = -1;

//!Constructeur par paramètre pour intialiser les attributs de la classe. 
//! \param nom				Nom du médecin
//! \param numeroLicence	id du médecin	
//! \param specialite		spécialité du médecin
Medecin::Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite):Personnel(nom, numeroLicence),specialite_(specialite),nbConsultations_(0)
{}


//! Operateur qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Medecin::operator+=(Patient* patient)
{
	if (patient && !chercherPatient(patient->getNumeroAssuranceMaladie())) {
		patientsAssocies_.push_back(patient);

		return true;
	}

	return false;
}

//! Operateur qui supprime un patient de la liste des patients
//! \param numeroAssuranceMaladiePatient Le patient à ajouter
//! \return      Un bool qui indique si l'opération a bien fonctionnée
bool Medecin::operator-=(const std::string& numeroAssuranceMaladiePatient)
{
	int indexPatient = trouverIndexPatient(numeroAssuranceMaladiePatient);
	if (indexPatient == PATIENT_INEXSISTANT)
	{
		return false;
	}

	patientsAssocies_.erase(patientsAssocies_.begin() + indexPatient);

	return true;
}

//! Méthode qui affiche les informations du médecin 
//! \param stream	Le stream dans lequel on affiche les infromations
//! \return			stream qui contient les informations du médecin
void Medecin::afficher(std::ostream& stream) const
{
	static const std::string SPECIALITES[] = { "Generaliste",
												"Cardiologue",
												"Dermatologue",
												"Gynecologue",
												"Pediatre",
												"Ophtalmologue",
												"Autre" };
	auto index = enum_value(specialite_);
	assert(valid_as_enum<Medecin::Specialite>(index));
	std::string specialite = SPECIALITES[index];

	//Afficher les informations du médecin liées à la classe Personnel
	Personnel::afficher(stream);

	stream << "\n\tSpecialite: " << specialite
		<< (patientsAssocies_.empty() ? "\n\tAucun patient n'est suivi par ce medecin." : "\n\tPatients associes:");

	for (const auto& patient : patientsAssocies_)
	{
		stream << "\n\t\t";
		//Afficher les informations du Patient
		patient->afficher(stream);
	}
}

//! Méhode qui cherche un patient par numero d'assurance maladie
//! \param numeroAssuranceMaladie Le numero d'assurance maladie Le numero d'assurance maladie du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* Medecin::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (auto& patientsAssocie : patientsAssocies_)
	{
		if (*patientsAssocie == numeroAssuranceMaladie)
		{
			return patientsAssocie;
		}
	}

	return nullptr;
}

//! Méthode qui incrémente le nombre de consultations d'un médecin 
void Medecin::incrementNombreConsultations() 
{
	nbConsultations_++;
}


//! Méthode qui retourne le salaire annuel du médecin
//! \return Le salaire annuel du médecin (= salaire de base du médecin + nombre de consultations * le prix de consultation)

double Medecin::getSalaireAnnuel() const 
{
	double salaireAnnuel;
	salaireAnnuel = SALAIRE_DE_BASE_MEDECIN + nbConsultations_ * getPrixConsultation();
	return salaireAnnuel;

}


//! Méthode retourne le prix de la consultation qui dépend de la spécialité du médecin.
//! \return prix de la consultation
double Medecin::getPrixConsultation() const 
{
	switch (specialite_) {
	case Specialite::Pediatre:
		return 80;
	case Specialite::Gynecologue:
		return 100;
	case Specialite::Ophtalmologue:
		return 100;
	case Specialite::Cardiologue:
		return 120;
	case Specialite::Dermatologue:
		return 120;
	case Specialite::Generaliste:
		return 60;
	case Specialite::Autre:
		return 60;
	default:
		throw "La spécialite du médecin n'est pas définie";
	}

}

size_t Medecin::getNombreConsultations() const
{
	return nbConsultations_;
}


//! Méthode qui retourne la specialite du medecin
//! \return la specialite des medecins
const Medecin::Specialite Medecin::getSpecialite() const
{

	return specialite_;
}

//! Méthode qui retourne le nombre de patients associés
//! \return le nombre de patients associés
const size_t Medecin::getNombrePatientsAssocies() const
{

	return patientsAssocies_.size();
}


//! Méthode qui retourne la liste des patients associes au medecin
//! \return la liste des patients
const std::vector<Patient*>& Medecin::getPatientsAssocies() const
{
	return patientsAssocies_;
}


//! Méthode qui met a jours la specialité du medecin
//! \param  specialite  specialité du medecin
void Medecin::setSpecialite(Specialite specialite)
{
	specialite_ = specialite;
}


//! Méthode  qui permet de trouver l'index d'un medecin dans la liste des medecins
//! \param numeroLicence   numero de licence du medecin
//! \return             int bool qui indique l'index du medecin et MEDECIN_INEXSISTANT si le medecin est inexistant
int Medecin::trouverIndexPatient(const std::string& numeroAssuranceMaladie)
{
	for (std::size_t i = 0; i < patientsAssocies_.size(); i++)
	{
		if (*patientsAssocies_[i] == numeroAssuranceMaladie)
		{
			return static_cast<int>(i);
		}
	}
	return PATIENT_INEXSISTANT;
}
