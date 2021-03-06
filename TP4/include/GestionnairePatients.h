//! Définition de la classe GestionnairePatients qui permet de gérer les patients
//! \authors Didier Blach-Lafleche & Maude Tremblay
//! \date 14 juin 2020

#ifndef GESTIONNAIREPATIENTS_H
#define GESTIONNAIREPATIENTS_H

#include <string>
#include "Patient.h"
#include <memory>
#include "vector"
#include "PatientEtudiant.h"
#include "utils.h"
#include "Foncteurs.h"


class GestionnairePatients
{
public:
    enum class TypePatient
    {
        first_ = -1,
        Patient,
        PatientEtudiant,
        last_
    };

    GestionnairePatients();

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    bool chargerDepuisFichier(const std::string& nomFichier);

    //! Méthode qui ajoute un patient à l'objet GestionnairePatient
    //! \param patient référence vers l'objet à jouter
    //! \return true si le patient a été ajouté, false sinon
    template<typename T>
    bool ajouterPatient(const T& patient) {
        if (!chercherPatient(patient.getNumeroAssuranceMaladie())) {

            if (patients_.size() >= NB_PATIENT_MAX)
            {
                return false;
            }
            patients_.push_back(std::make_shared<T>(patient));
            return true;
        }
        return false;
    };

    bool supprimerPatient(const std::string& numeroAssMaladie);
    friend std::ostream& operator<<(std::ostream& os, const GestionnairePatients& gestionnairePatient);
    const std::vector<std::shared_ptr<Patient>>& getPatients() const;
    std::vector<std::shared_ptr<Patient>> getPatientsEtudiants() const;

    size_t getNbPatients() const;
    size_t getNbPatientsEtudiants() const;

    static constexpr size_t NB_PATIENT_MAX = 100;

private:
    bool lireLignePatient(const std::string& ligne);

    std::vector<std::shared_ptr<Patient>> patients_;
};

#endif // GESTIONNAIREPATIENTS_H