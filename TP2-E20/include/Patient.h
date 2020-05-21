//! Définition de la classe Medecin qui représente un patient de l'hôpital
//! \authors Didier Blach Laflèche & Maude Tremblay
//! \date 21 Mai 2020

#ifndef PATIENT_H
#define PATIENT_H

#include <string>

class Patient
{
public:
    Patient() = default;
    Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie);

    // surcharge interne d'operateurs
    bool operator==(const std::string& string) const;
    // surcharge externe d'operateurs
    friend std::ostream& operator<<(std::ostream& stream, const Patient& patient);
    friend bool operator==(const std::string& string, const Patient& patient);

    // getters
    const std::string& getNom() const;
    const std::string& getNumeroAssuranceMaladie() const;
    const std::string& getDateDeNaissance() const;

    // setters
    void setNom(const std::string& nom);
    void setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie);
    void setDateDeNaissance(const std::string& dateDeNaissance);

private:
    // Attributs
    std::string nom_;
    std::string numeroAssuranceMaladie_;
    std::string dateDeNaissance_;
};

#endif // PATIENT_H

