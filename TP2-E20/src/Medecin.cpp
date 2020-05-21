//! Définition de la classe Medecin qui représente un médecin qui travaille à l'hôpital
//! \authors Didier Blach Laflèche & Maude Tremblay
//! \date 20 Mai 2020

#include <iostream>
#include "Medecin.h"
#include "typesafe_enum.h"

constexpr std::size_t CAPACITE_PATIENTS_INITIALE = 2;

//! Constructeur par paramètre  de la classe Medecin
//! \param nom              Nom du medecin
//! \param numeroLicence    Numero de licence du medecin
//! \param specialite       Specialite du medecin
Medecin::Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite)
	: nom_(nom)
	, numeroLicence_(numeroLicence)
	, specialite_(specialite)
	, patientsAssocies_(std::vector<std::shared_ptr<Patient>>())
{
}

//! Surcharge de l'opérateur << : Affiche les informations du médecin
//! \param stream Le stream dans lequel on affiche les infos
//! \param medecin le médecin dont on veut afficher les informations
//| \return le stream qui affiche les infos
std::ostream& operator<< (std::ostream& stream, const Medecin& medecin)
{
	static const std::string SPECIALITES[] = { "Generaliste",
												"Cardiologue",
												"Dermatologue",
												"Gynecologue",
												"Pediatre",
												"Ophtalmologue",
												"Autre" };
	auto index = enum_value(medecin.specialite_);
	assert(valid_as_enum<Medecin::Specialite>(index));
	std::string specialite = SPECIALITES[index];

	std::string statut = medecin.estActif_ ? "Actif" : "Inactif";

	stream << "\nMedecin: " << medecin.nom_
		<< "\n\tNumero de licence: " << medecin.numeroLicence_
		<< "\n\tSpecialite: " << specialite
		<< "\n\tStatut: " << statut
		<< (medecin.patientsAssocies_.size()== 0 ? "\n\tAucun patient n'est suivi par ce medecin." : "\n\tPatients associes:");

	if (medecin.patientsAssocies_.size() > 0)
	{
		for (std::size_t i = 0; i < medecin.patientsAssocies_.size(); i++)
		{
			stream << "\n\t\t" << *(medecin.patientsAssocies_[i]);
		}
	}
	stream << '\n';

	return stream;
}


//! Surcharge de l'opérateur += : opérateur pour ajouter un patient
//! \param patient Patient à ajouter
//! \return true si l'ajout a réussi, sinon false
bool Medecin::operator+= (const Patient& patient)
{
	int nbPatientInit = patientsAssocies_.size();

	patientsAssocies_.push_back(std::make_shared<Patient>(patient));


	if((nbPatientInit+1)==patientsAssocies_.size())
	{ 
		return true;
	}
	else
	{
		return false;
	}
}

//! Surcharge de l'opérateur -= : opérateur pour supprimer un patient
//! \param nummeroAssuranceMaladie Numéro d'assurance Maladie du patient à supprimer
//! \return true si la suppression a réussi, sinon false
bool Medecin::operator-= (const std::string& numeroAssuranceMaladie)
{
	for (size_t i = 0; i < patientsAssocies_.size(); i++)
	{
		if (patientsAssocies_[i]->getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			patientsAssocies_[i].reset();

			for (size_t j = i; j < patientsAssocies_.size() - 1; j++)
			{
				patientsAssocies_[j] = patientsAssocies_[j + 1];
			}

			patientsAssocies_.pop_back();

			return true;
		}
	}

	return false;
}

//! Surcharge de l'opérateur == : compare un string avec le numéro de la licence du médecin 
//! \param numeroLicence numéro de licence à comparer
//! \return true si le numéro de licence correspond à celui du médecin, sinon false
bool Medecin::operator== (const std::string& numeroLicence)
{
	return numeroLicence == numeroLicence_;
}

//! Surcharge externe de l'opérateur == :compare un string avec le numéro de la licence du médecin 
//! \param numeroLicence numéro de licence à comparer
//! \param medecin Medecin avec lequel comparer le numéro de licence
//! \return true si le numéro de licence correspond à celui du médecin, sinon false
bool operator==(const std::string& numeroLicence, Medecin medecin)
{
	return numeroLicence == medecin.getNumeroLicence();
}


//! Méthode qui permet de chercher un patient avec son numéro d'assurance maladie
//! \param numeroAssuranceMaladie numéro d'assurance maladie du patient
//! \return pointeur brut du patient s'il est trouvé, sinon nullptr
Patient* Medecin::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (size_t i = 0; i < patientsAssocies_.size(); i++)
	{
		if (patientsAssocies_[i]->getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{

			return patientsAssocies_[i].get();
		}
	}

	return nullptr;
}



//! Méthode qui retourne le nom du medecin
//! \return le nom du medecin 
const std::string& Medecin::getNom() const
{

	return nom_;
}


//! Méthode qui retourne le numero de licence du medecin
//! \return le numero de licence
const std::string& Medecin::getNumeroLicence() const
{

	return numeroLicence_;
}

//! Méthode qui retourne le status du medecin
//! \return le status du medecin
bool Medecin::getEstActif() const
{

	return estActif_;
}

//! Méthode qui retourne la specialite du medecin
//! \return la specialite des medecins
const Medecin::Specialite Medecin::getSpecialite() const
{

	return specialite_;
}

//! Méthode qui retourne le nombre de patients associés au  médecin
//! \return le nombre patient associes
const size_t Medecin::getNombrePatientsAssocies() const
{

	return patientsAssocies_.size();
}

//! Méthode qui retourne la capacité du tableau patientsAssocies_
//! \return la capacité du tableau patientsAssocies_
const size_t Medecin::getCapacitePatientAssocies() const
{

	return patientsAssocies_.capacity();
}

//! Méthode qui retourne la liste des patients associes au medecin
//! \return la liste des patients
std::vector<std::shared_ptr<Patient>> Medecin::getPatientsAssocies()
{
	return patientsAssocies_;
}

//! Méthode qui met a jours le nom  du medecin
//! \pararm  nom  Le nom du médecin
void Medecin::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui met a jours le numero de licence du medecin
//! \pararm  numeroLicence  le numero de licence du medecin
void Medecin::setNumeroLicence(const std::string& numeroLicence)
{
	numeroLicence_ = numeroLicence;
}

//! Méthode qui met a jours le statut du medecin si il est actif ou non
//! \pararm  boolean indiquant le  nouveau status du medecin
void Medecin::setEstActif(bool estActif)
{

	estActif_ = estActif;
}

//! Méthode qui met a jours la specialité du medecin
//! \pararm  specialite  specialité du medecin
void Medecin::setSpecialite(Specialite specialite)
{
	specialite_ = specialite;
}
