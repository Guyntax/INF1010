#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <sstream>
class Patient
{
public:
    Patient() = default;
    Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie);

    // opérateur== qui compare un string avec le numéro d'assurance de maladie d'un patient
    // (par exemple, pour patient == "TREMR124520")
    bool operator==(const std::string& string) const;

    const std::string& getNom() const;
    const std::string& getNumeroAssuranceMaladie() const;
    const std::string& getDateDeNaissance() const;

    void setNom(const std::string& nom);
    void setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie);
    void setDateDeNaissance(const std::string& dateDeNaissance);

   friend std::stringstream& operator<<(std::stringstream& stream, const Patient& patient);
   friend bool operator==(const std::string& string, const Patient& patient);
private:
    std::string nom_;
    std::string numeroAssuranceMaladie_;
    std::string dateDeNaissance_;
};

#endif // PATIENT_H

