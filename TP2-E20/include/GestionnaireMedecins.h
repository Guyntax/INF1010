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
    bool operator+= (Medecin medecin);
    bool operator-=(const std::string& numeroLicence);
    friend std::ostream& operator<<(std::ostream& stream, const GestionnaireMedecins& gestMed);
 
    size_t getNbMedecins() const;
    const std::vector<std::shared_ptr<Medecin>>& getMedecins() const;
    size_t getCapaciteMedecins() const;

private:
    bool lireLigneMedecin(const std::string& ligne);
    int trouverIndexMedecin(const std::string& numeroLicence);

    std::vector<std::shared_ptr<Medecin>> medecins_;
};

#endif // GESTIONNAIREMEDECIN_H