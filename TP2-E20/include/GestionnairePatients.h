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

    // opérateur+= qui remplace ajouterPatient
    bool operator+=(const std::shared_ptr<Patient>& patient);

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    bool chargerDepuisFichier(const std::string& nomFichier);





    //signature de getPatients()  retourne une reference constante vers le vecteur patients_
    std::vector<std::shared_ptr<Patient>> getPatients() const;

    static constexpr size_t NB_PATIENT_MAX = 16;

    friend std::ostream& operator<<(std::ostream& stream, const GestionnairePatients& gestionnairePatients);

private:
    bool lireLignePatient(const std::string& ligne);

    //TODO : remplacer le tableau par un vecteur de shared_ptr de Patient
    std::vector<std::shared_ptr<Patient>> patients_;// (NB_PATIENT_MAX);

};

#endif // GESTIONNAIREPATIENTS_H


