//TODO : Entête de fichier
#include "Personnel.h"
#include <iostream>
#include <typeinfo>

//! Constructeur par paramètre  de la classe de base Personnel
//! \param nom Nom du personnel
//! \param id  L'identifiant du personnel
Personnel::Personnel(const std::string& nom, const std::string& id) : nom_(nom), id_(id)
{
}

//! Opérateur qui compare un string avec l'identifiant du personnel avec un personnel comme opérande de gauche
//! \param id  L'identifiant  avec le quel on veut comparé le personnel
//! \return vrai si  Les identifiants sont identiques, faux sinon
bool Personnel::operator==(const std::string& id) const
{
	return (id_ == id);
}

//! Opérateur qui comparel'identifiant du personnel avec l'identifiant opérande de gauche.
//! \param id l'identifiant avec le quel on veut comparé le personnel
//! \param personnel le personne avec lequel on compare  de l'identifiant
bool operator==(const std::string& id, const Personnel& personnel)
{
	return (id == personnel.id_);
}

//TODO : méthode afficher
void Personnel::afficher(std::ostream& os) const
{
	std::string typePersonnel = //TODO: Chercher le nom de la classe.Elle peut être Medecin ou MedecinResident.
		                        //Utiliser typeid().name() ;
	os << "Personnel: " << // Afficher nom_
		<< "\n\tType: " << // Extraire le nom de la classe du string typePersonnel
		<< "\n\tIdentifiant: " << //Afficher id_
		<< "\n\tStatut: " << // afficher 'Actif' si estActif est true et 'Inactif' si false;
}

//! Méthode qui retourne le nom du personnel
//! \return le nom du personnel 
const std::string& Personnel::getNom() const
{

	return nom_;
}


//! Méthode qui retourne l'identifiant du personnel
//! \return id_ l'identifiant du personnel
const std::string& Personnel::getId() const
{

	return id_;
}

//! Méthode qui retourne le status du personnel
//! \return estActif_ le status du personnel
bool Personnel::getEstActif() const
{

	return estActif_;
}

//! Méthode qui met a jours le nom  du personnel
//! \pararm  nom  Le nom du personnel
void Personnel::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui met a jours l'identifiant du personnel
//! \pararm  id  l'identifiant du personnel
void Personnel::setId(const std::string& id)
{
	id_ = id;
}

//! Méthode qui met a jours le statut  du personnel s' il est actif ou non
//! \pararm  boolean indiquant le  nouveau status du personnel
void Personnel::setEstActif(bool estActif)
{
	estActif_ = estActif;
}
