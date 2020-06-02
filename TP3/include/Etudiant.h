//! Définition de la classe abstraite Étudiant qui représente un étudiant
//! \Authurs: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <string>

class Etudiant
{
public:
    Etudiant() = default;
    Etudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, const std::string& etablissement);

    //méthode virtuelle pure.
    virtual void afficher(std::ostream& stream) const =0;

    const std::string& getNom() const;
    const std::string& getMatricule() const;
    const std::string& getDateDeNaissance() const;
    const std::string& getEtablissement() const;

    void setNom(const std::string& nom);
    void setMatricule(const std::string& matricule);
    void setDateDeNaissance(const std::string& dateDeNaissance);
    void setEtablissement(const std::string& etablissement);

protected:
    std::string etablissement_;
private:
    std::string nom_;
    std::string matricule_;
    std::string dateDeNaissance_;
};

#endif // ETUDIANT_H