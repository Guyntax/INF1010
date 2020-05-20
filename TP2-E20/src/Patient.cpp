// TODO: Faire l'entête de fichier

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




// TODO : Opérateur == qui compare un string avec le numero d'assurance maladie du patient avec patient comme opérande de gauche
bool Patient::operator==(const std::string& string) const {
	if (numeroAssuranceMaladie_ == string) {
		return true;
	};
	return false;
}
// TODO : Opérateur == qui compare le numero d'assurance maladie du patient avec le numero d'assurance comme opérande de gauche.





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





// opérateur<< qui remplace afficherstd::stringstream operator<<(std::ostream& stream,const Patient& patient);
//! Méthode qui affiche les informations d'un patient
//! \param stream Le stream dans lequel afficher

/*
std::stringstream& operator<<(std::stringstream& stream, const Patient& patient) {
	return stream << "Patient: " << patient.nom_ << " | Date de naissance: " << patient.dateDeNaissance_
		<< " | Numero d\'assurance maladie: " << patient.numeroAssuranceMaladie_;
}
*/

std::ostream& operator<<(std::ostream& stream, const Patient& patient){
	 return stream << "Patient: " << patient.nom_ << " | Date de naissance: " << patient.dateDeNaissance_
		<< " | Numero d\'assurance maladie: " << patient.numeroAssuranceMaladie_;
}


// opérateur== qi compare un string avec le numéro d'assurance de maladie d'un patient
// (par exemple, pour "TREMR124520" == patient)

bool operator==(const std::string& string, const Patient& patient) {
	if (patient.numeroAssuranceMaladie_ == string) {
		return true;
	};
	return false;
}