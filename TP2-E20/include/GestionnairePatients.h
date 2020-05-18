#ifndef GESTIONNAIREPATIENTS_H
#define GESTIONNAIREPATIENTS_H

#include <string>
#include "Patient.h"
#include <memory>


class GestionnairePatients
{
public:
    GestionnairePatients();

    bool ajouterPatient(const Patient& patient);
    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    bool chargerDepuisFichier(const std::string& nomFichier);
    void afficher(std::ostream& stream) const;

    // TODO : signature des opérateurs à surcharger.
    // opérateur<< qui remplace afficher
    // opérateur+= qui remplace ajouterPatient


    size_t getNbPatients() const;
    // TODO : signature de getPatients()  retourne une reference constante vers le vecteur patients_

    static constexpr size_t NB_PATIENT_MAX = 16;

private:
    bool lireLignePatient(const std::string& ligne);

    //TODO : remplacer le tableau par un vecteur de shared_ptr de Patient
    Patient patients_[NB_PATIENT_MAX];
    size_t nbPatients_;
};

#endif // GESTIONNAIREPATIENTS_H