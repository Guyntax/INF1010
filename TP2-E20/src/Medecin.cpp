// TODO: Faire l'entête de fichier

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
	, nbPatientsAssocies_(0)
	, capacitePatientsAssocies_(CAPACITE_PATIENTS_INITIALE)
	, patientsAssocies_(std::make_unique<std::shared_ptr<Patient>[]>(CAPACITE_PATIENTS_INITIALE))
{
}


// TODO: Methode ajouterPatient doit être remplacée par l'operateur +=. il prend en paramètre le patient à ajouter
// Retourne true si l'opération d'ajout est réussi, false si non.

//! Méthode qui ajoute un patient à liste des patients associes au médecin.
//! \param Patient patient à ajouter
void Medecin::ajouterPatient(Patient patient)
{
	static constexpr unsigned int AUGMENTATION_NOMBRE_PATIENTS = 2;

	// Verifier si assez de mémoire est allouée
	if (nbPatientsAssocies_ >= capacitePatientsAssocies_)
	{
		// Creer nouveau tableau
		std::unique_ptr<std::shared_ptr<Patient>[]> tableauTemporaire =
			std::make_unique<std::shared_ptr<Patient>[]>(capacitePatientsAssocies_ * AUGMENTATION_NOMBRE_PATIENTS);

		// Copier chaque élément vers le nouveau tableau
		for (std::size_t i = 0; i < nbPatientsAssocies_; i++)
		{
			tableauTemporaire[i] = patientsAssocies_[i];
		}

		patientsAssocies_ = move(tableauTemporaire);
		capacitePatientsAssocies_ *= AUGMENTATION_NOMBRE_PATIENTS;
	}

	patientsAssocies_[nbPatientsAssocies_++] = std::make_shared<Patient>(patient);
}


// TODO: Methode supprimerPatient doit être remplacée par l'operateur -= Il prend en paramètre le numero d'assurance maladie du patient 
// Retourne true si l'opération d'ajout est réussi, false si non.

//! Méthode pour supprimer un patient de la liste des patients
//! \param le nom du patient a supprimer
bool Medecin::supprimerPatient(const std::string& numeroAssuranceMaladie)
{
	for (size_t i = 0; i < nbPatientsAssocies_; i++)
	{
		if (patientsAssocies_[i]->getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			patientsAssocies_[i].reset();

			for (size_t j = i; j < nbPatientsAssocies_ - 1; j++)
			{
				patientsAssocies_[j] = patientsAssocies_[j + 1];
			}

			patientsAssocies_[nbPatientsAssocies_ - 1] = nullptr;
			nbPatientsAssocies_--;

			return true;
		}
	}

	return false;
}
// TODO : La methode afficher doit être remplacée par l’opérateur << 
//! Méthode pour afficher les informations du medecin
//! \param stream dans lequel on ecrit les informations du medecin
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
	assert(valid_as_enum<Specialite>(index));
	std::string specialite = SPECIALITES[index];

	std::string statut = estActif_ ? "Actif" : "Inactif";

	stream << "\nMedecin: " << nom_
		<< "\n\tNumero de licence: " << numeroLicence_
		<< "\n\tSpecialite: " << specialite
		<< "\n\tStatut: " << statut
		<< (nbPatientsAssocies_ == 0 ? "\n\tAucun patient n'est suivi par ce medecin." : "\n\tPatients associes:");

	for (std::size_t i = 0; i < nbPatientsAssocies_; i++)
	{
		stream << "\n\t\t";
		patientsAssocies_[i]->afficher(stream);
	}
	stream << '\n';
}

// TODO : Opérateur == qui compare un string avec le numéro de la  licence du médecin avec medécin comme opérande de gauche

// TODO :  Opérateur ==  qui compare le numéro de la  licence du médecin avec un le numéro de la  licence. Le numéro de licence comme opérande de gauche.

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

	return nbPatientsAssocies_;
}

//! Méthode qui retourne la capacité du tableau patientsAssocies_
//! \return la capacité du tableau patientsAssocies_
const size_t Medecin::getCapacitePatientAssocies() const
{

	return capacitePatientsAssocies_;
}

//! Méthode qui retourne la liste des patients associes au medecin
//! \return la liste des patients
std::unique_ptr<std::shared_ptr<Patient>[]> Medecin::getPatientsAssocies()
{
	return move(patientsAssocies_);
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
