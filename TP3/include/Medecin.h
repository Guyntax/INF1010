//! Définition de la classe Medecin qui hérite de Personnel. Cette classe représente un médecin qui exerce dans l'hôpital.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#ifndef MEDECIN_H
#define MEDECIN_H

#include <memory>
#include <string>
#include "Patient.h"
#include <vector>
#include "Personnel.h"


class Medecin : public Personnel
{
public:
    enum class Specialite
    {
        first_ = -1,
        Generaliste,
        Cardiologue,
        Dermatologue,
        Gynecologue,
        Pediatre,
        Ophtalmologue,
        Autre,
        last_
    };

    Medecin() = default;
    Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite);

    bool operator+=(Patient* patient);
    bool operator-=(const std::string& numeroAssuranceMaladiePatient);

    
    virtual void afficher(std::ostream& stream) const override;

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    void incrementNombreConsultations();

    virtual double getSalaireAnnuel() const override;
    double getPrixConsultation() const;
    size_t getNombreConsultations() const;
    const Specialite getSpecialite() const;
    const size_t getNombrePatientsAssocies() const;
    const std::vector<Patient*>& getPatientsAssocies() const;

    void setSpecialite(Specialite specialite);

    static constexpr size_t SALAIRE_DE_BASE_MEDECIN = 100000;


protected:
// Attributs
    Specialite specialite_;
    size_t nbConsultations_;
    std::vector<Patient*> patientsAssocies_;


private:
    int trouverIndexPatient(const std::string& numeroAssuranceMaladie);

    
};

#endif // MEDECIN_H