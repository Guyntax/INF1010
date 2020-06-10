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

    // TODO: Remplacer l'opérateur par la méthode générique ajouterPatient
    // La méthode prend une référence vers l'objet à ajouter
    template<typename T>
    bool ajouterPatient(const T& patient);

    // TODO : Ajouter la méthode supprimerPatient
    // Les paramètres : numero d'assurance Maladie de type string
    // Retourne un booléan
    bool supprimerPatient(const std::string& numeroAssMaladie);
    
    friend std::ostream& operator<<(std::ostream& os, const GestionnairePatients& gestionnairePatient);

    const std::vector<std::shared_ptr<Patient>>& getPatients() const;

    // DONE Modifier cette méthode.
    // Elle retourne un vecteur de pointeur shared_ptr vers Patient
    std::vector<std::shared_ptr<Patient>> getPatientsEtudiants() const;

    size_t getNbPatients() const;
    size_t getNbPatientsEtudiants() const;

    static constexpr size_t NB_PATIENT_MAX = 100;

private:
    bool lireLignePatient(const std::string& ligne);

    std::vector<std::shared_ptr<Patient>> patients_;
};

#endif // GESTIONNAIREPATIENTS_H