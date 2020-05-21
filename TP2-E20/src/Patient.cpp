//! Définition de la classe Medecin qui représente un patient de l'hôpital
//! \authors Didier Blach Laflèche & Maude Tremblay
//! \date 20 Mai 2020

#include "Patient.h"
#include <iostream>
#include <sstream>

//! Constructeur par paramètre  de la classe Patient
//! \param nom						Nom du patient
//! \param dateDeNaissance			Date de naissance du patient
//! \param numeroAssuranceMaladie	Le numero d'assurance maladie du patient
Patient::Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie)
	: nom_(nom)
	, dateDeNaissance_(dateDeNaissance)
	, numeroAssuranceMaladie_(numeroAssuranceMaladie)
{
}


//! Surcharge de l'opérateur == : compare un string avec le numéro d'assurance maladie du patient
//! \param string numéro d'assurance maladie du patient à comparer
//! \return true si le numéro d'assurance maladie correspond`à celui du patient, sinon false
bool Patient::operator==(const std::string& string) const {
	if (numeroAssuranceMaladie_ == string) {
		return true;
	};
	return false;
}


//! Méthode qui retourne le nom du patient
//! \return le nom du patient 
const std::string& Patient::getNom() const
{

	return nom_;
}

//! Méthode qui retourne le numéro d'assurance maladie du patient
//! \return le numéro d'assurance maladie du patient
const std::string& Patient::getNumeroAssuranceMaladie() const
{

	return numeroAssuranceMaladie_;
}

//! Méthode qui retourne la date de naissance du patient
//! \return la date de naissnace du patient 
const std::string& Patient::getDateDeNaissance() const
{

	return dateDeNaissance_;
}

//! Méthode qui permet de mettre à jour le nom du patient
//! \Param nom Le nom du patient
void Patient::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui permet de mettre à jour le nom du numero d'assurance maladie du patient
//! \Param numeroAssuranceMaladie le numero d'assurance maladie
void Patient::setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie)
{
	numeroAssuranceMaladie_ = numeroAssuranceMaladie;
}

//! Méthode qui permet de mettre à jour la date de naissance du patient
//! \Param dateDeNaissance date de naissance du patient
void Patient::setDateDeNaissance(const std::string& dateDeNaissance)
{
	dateDeNaissance_ = dateDeNaissance;
}


//! Surcharge de l'opérateur<< : affiche les informations d'un patient
//! \param stream Le stream dans lequel afficher
//! \param patient Patient dont on veut afficher les informations
//! \return stream Stream contenant les informations du patient
std::ostream& operator<<(std::ostream& stream, const Patient& patient){
	 return stream << "Patient: " << patient.nom_ << " | Date de naissance: " << patient.dateDeNaissance_
		<< " | Numero d\'assurance maladie: " << patient.numeroAssuranceMaladie_;
}

//! Surcharge externe de l'opérateur == :compare un string avec le numéro d'assurance maladie d'un patient 
//! \param string numéro D'assurance maladie à comparer
//! \param patient Patient avec lequel comparer le numéro d'assurance maladie
//! \return true si le numéro d'assurance maladie correspond à celui du patient, sinon false
bool operator==(const std::string& string, const Patient& patient) {
	if (patient.numeroAssuranceMaladie_ == string) {
		return true;
	};
	return false;
}