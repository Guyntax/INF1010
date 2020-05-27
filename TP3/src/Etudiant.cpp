//TODO Entête du fichier
#include "Etudiant.h"
#include <iostream>
#include <string>

//Le constructeur par paramètres. Utiliser la liste d'initialisation
Etudiant::Etudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, const std::string& etablissement):
    etablissement_(etablissement),
    nom_(nom),
    matricule_(matricule),
    dateDeNaissance_(dateDeNaissance),
{}

//! Méthode qui affiche les informations de l'étudiant
//! \param os Le stream dans lequel afficher
void Etudiant::afficher(std::ostream& stream) const
{
	stream << "Matricule: " << matricule_ << "\n\tEtablissement: " << etablissement_;
}

const std::string& Etudiant::getNom() const { return nom_; };
const std::string& Etudiant::getMatricule() const { return matricule_; };
const std::string& Etudiant::getDateDeNaissance() const { return dateDeNaissance_; };
const std::string& Etudiant::getEtablissement() const { return etablissement_; };

void Etudiant::setNom(const std::string& nom) { nom_ = nom; };
void Etudiant::setMatricule(const std::string& numeroAssuranceMaladie) { matricule_ = numeroAssuranceMaladie; };
void Etudiant::setDateDeNaissance(const std::string& dateDeNaissance) {dateDeNaissance_ = dateDeNaissance ;};
void Etudiant::setEtablissement(const std::string& etablissement) { etablissement_ = etablissement; };