#ifndef GESTIONNAIREMEDECIN_H
#define GESTIONNAIREMEDECIN_H

#include <memory>
#include "Medecin.h"
#include "GestionnairePatients.h"


class GestionnaireMedecins
{
public:
    GestionnaireMedecins();
    //TODO : signature de constructeur de copie
    //TODO : signature d'operateur d'affectaion

    void ajouterMedecin(std::shared_ptr<Medecin> medecin);
    Medecin* chercherMedecin(const std::string& numeroLicence);
    bool chargerDepuisFichier(const std::string& nomFichiers);
    bool supprimerMedecin(const std::string& numeroLicence);
    void afficher(std::ostream& stream) const;

    // TODO : signature des opérateurs à surcharger.
    // opérateur<< qui remplace afficher
    // opérateur+= qui remplace ajouterMedecin
    // opérateur-= qui remplace supprimerMedecin


    size_t getNbMedecins() const;
    size_t getCapaciteMedecins() const;
    // TODO : signature de getMedecins() retourne une reference constante vers le vecteur medecins_

private:
    bool lireLigneMedecin(const std::string& ligne);
    int trouverIndexMedecin(const std::string& numeroLicence);

    // TODO: remplacer le tableau par un vecteur de shared_ptr de medecin
    size_t nbMedecins_;
    size_t capaciteMedecins_;
    std::unique_ptr<std::shared_ptr<Medecin>[]> medecins_;
};

#endif // GESTIONNAIREMEDECIN_H