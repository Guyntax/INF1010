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

    // TODO : la signature de l'opérateur à surcharger
    // opérateur<< pour afficher 
    std::stringstream& operator<<(std::stringstream& string);

    Medecin* getMedecin() const;
    Patient* getPatient() const;
	const std::string& getDate() const;


private:
    Medecin* medecin_;
    Patient* patient_;
    std::string date_;
};

#endif // CONSULTATION_H