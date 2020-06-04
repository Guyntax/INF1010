//! Implémentation de la classe Étudiant qui est une classe abstraite qui représente un étudiant 
//! \Authurs: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#include "Etudiant.h"
#include <iostream>
#include <string>

//! Constructeur par paramètres
//! \param nom					Nom de l'étudiant
//! \param date	de naissance	Date de naissance de l'étudiant
//! \param matricule			matricule de l'étudiant
//! \param établissement		établissement de l'étudiant
Etudiant::Etudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, const std::string& etablissement):
    etablissement_(etablissement),
    nom_(nom),
    matricule_(matricule),
    dateDeNaissance_(dateDeNaissance)
{}

//! Méthode qui affiche les informations de l'étudiant
//! \param os Le stream dans lequel afficher
void Etudiant::afficher(std::ostream& stream) const
{
    //! \return le stream qui contient les informations
	stream << "Matricule: " << matricule_ << "\n\tEtablissement: " << etablissement_;
}

//! Méthode qui retourne le nom de l'étudiant
//! \return	nom de l'étudiant
const std::string& Etudiant::getNom() const { return nom_; };

//! Méthode qui retourne le matricule de l'étudiant
//! \return	matricule de l'étudiant
const std::string& Etudiant::getMatricule() const { return matricule_; };

//! Méthode qui retourne la date de naissance de l'étudiant
//! \return	date de naissance de l'étudiant
const std::string& Etudiant::getDateDeNaissance() const { return dateDeNaissance_; };

//! Méthode qui retourne l'etablissment de l'étudiant
//! \return	l'etablissment de l'étudiant
const std::string& Etudiant::getEtablissement() const { return etablissement_; };

//! Méthode qui set le nom de l'étudiant
//! \param	nom Nom de l'étudiant
void Etudiant::setNom(const std::string& nom) { nom_ = nom; };

//! Méthode qui set le matricule de l'étudiant
//! \param	matricule   Matricule de l'étudiant
void Etudiant::setMatricule(const std::string& matricule) { matricule_ = matricule; };

//! Méthode qui set la date de naissance de l'étudiant
//! \param dateDeNaissance Date de naissance de l'étudiant
void Etudiant::setDateDeNaissance(const std::string& dateDeNaissance) {dateDeNaissance_ = dateDeNaissance ;};

//! Méthode qui set l'établissement de l'étudiant
//! \param etablissement    Établissement de l'étudiant
void Etudiant::setEtablissement(const std::string& etablissement) { etablissement_ = etablissement; };