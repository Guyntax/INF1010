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

    bool operator+=(const Patient& patient);

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    bool chargerDepuisFichier(const std::string& nomFichier);

    std::vector<std::shared_ptr<Patient>> getPatients() const;
    int getNbPatients()const;

    static constexpr size_t NB_PATIENT_MAX = 16;

    friend std::ostream& operator<<(std::ostream& stream, const GestionnairePatients& gestionnairePatients);

private:
    bool lireLignePatient(const std::string& ligne);

    std::vector<std::shared_ptr<Patient>> patients_;

};

#endif // GESTIONNAIREPATIENTS_H


