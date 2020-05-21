//! Définition de la classe GestionnairePatients qui permet la gestion des patients de l'hôpital
//! \authors Didier Blach Laflèche & Maude Tremblay
//! \date 21 Mai 2020

#ifndef GESTIONNAIREPATIENTS_H
#define GESTIONNAIREPATIENTS_H

#include <string>
#include "Patient.h"
#include <memory>
#include <vector>



class GestionnairePatients
{
public:
    GestionnairePatients();
    GestionnairePatients(const GestionnairePatients& gestPat);
    GestionnairePatients& operator=(const GestionnairePatients& gestionnairePatient);

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    bool chargerDepuisFichier(const std::string& nomFichier);

    // surcharge interne d'operateurs
    bool operator+=(const Patient& patient);
    // surcharge externe d'operateurs
    friend std::ostream& operator<<(std::ostream& stream, const GestionnairePatients& gestionnairePatients);

    // getters
    std::vector<std::shared_ptr<Patient>> getPatients() const;
    int getNbPatients()const;

    static constexpr size_t NB_PATIENT_MAX = 16;

private:
    // methodes privees
    bool lireLignePatient(const std::string& ligne);

    // attributs
    std::vector<std::shared_ptr<Patient>> patients_;

};

#endif // GESTIONNAIREPATIENTS_H


