//! Définition de la classe GestionnaireMedecins qui permet la gestion des médecins de l'hôpital
//! \authors Didier Blach Laflèche & Maude Tremblay
//! \date 21 Mai 2020

#ifndef GESTIONNAIREMEDECIN_H
#define GESTIONNAIREMEDECIN_H

#include <memory>
#include <vector>
#include<iostream>
#include "Medecin.h"
#include "GestionnairePatients.h"


class GestionnaireMedecins
{
public:
    GestionnaireMedecins();
    GestionnaireMedecins(const GestionnaireMedecins& gestionnaireMedecins);
    GestionnaireMedecins& operator=(const GestionnaireMedecins& gestionnaireMedecins);

    Medecin* chercherMedecin(const std::string& numeroLicence) const;
    bool chargerDepuisFichier(const std::string& nomFichiers);

    // surcharge interne d'operateurs
    bool operator+= (const Medecin& medecin);
    bool operator-=(const std::string& numeroLicence);
    // surcharge externe d'operateurs
    friend std::ostream& operator<<(std::ostream& stream, const GestionnaireMedecins& gestMed);
    
    // getters
    size_t getNbMedecins() const;
    const std::vector<std::shared_ptr<Medecin>>& getMedecins() const;
    size_t getCapaciteMedecins() const;

private:
    // methodes privees
    bool lireLigneMedecin(const std::string& ligne);
    int trouverIndexMedecin(const std::string& numeroLicence);

    // attributs
    std::vector<std::shared_ptr<Medecin>> medecins_;
};

#endif // GESTIONNAIREMEDECIN_H