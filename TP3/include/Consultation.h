//! Définition de la classe abstraite Consultation qui permet de gérer les consultations de l’hôpital.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#ifndef CONSULTATION_H
#define CONSULTATION_H

#include <string>
#include "Medecin.h"
#include "Patient.h"

class Consultation
{
public:
    Consultation() = default;
    Consultation(Medecin& medecin, Patient& patient, const std::string& date);

    Medecin* getMedecin() const;
    Patient* getPatient() const;
    const std::string& getDate() const;

    void afficher(std::ostream& os) const;

    // méthode virtuelle pure
    virtual const double calculerPrix() const =0;

    const double PRIX_DE_BASE = 50;

protected:
    Medecin* medecin_;
    Patient* patient_;
    std::string date_;
    double prix_;
};

#endif // CONSULTATION_H