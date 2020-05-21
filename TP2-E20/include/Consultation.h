//! Définition de la classe Consultation qui permet la gestion des consultations de l'hôpital
//! \authors Didier Blach Laflèche & Maude Tremblay
//! \date 21 Mai 2020

#ifndef CONSULTATION_H
#define CONSULTATION_H

#include <string>
#include<sstream>
#include "Medecin.h"
#include "Patient.h"

class Consultation
{
public:
    Consultation() = default;
	Consultation(Medecin& medecin, Patient& patient, const std::string& date);

    // surcharge externe d'operateurs
    friend std::ostream& operator<<(std::ostream& string, const Consultation& consultation);

    // getters
    Medecin* getMedecin() const;
    Patient* getPatient() const;
	const std::string& getDate() const;


private:
    // attributs
    Medecin* medecin_;
    Patient* patient_;
    std::string date_;
};

#endif // CONSULTATION_H