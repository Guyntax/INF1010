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

    // TODO calculerPrix méthode virtuelle pure qui retourne le prix de la consultation. A ne pas implémenter
    const double calculerPrix() const;

    const double PRIX_DE_BASE = 50;

//TODO : ces attributs doivent être accessibles par les classes dérivées de cette class
private:
    Medecin* medecin_;
    Patient* patient_;
    std::string date_;
    double prix_;
};

#endif // CONSULTATION_H