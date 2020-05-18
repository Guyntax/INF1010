#ifndef PATIENT_H
#define PATIENT_H

#include <string>


class Patient
{
public:
    Patient() = default;
    Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie);

    void afficher(std::ostream& stream) const;

    // TODO : la signature des opérateur  à surcharger
    // opérateur<< qui remplace afficher
    // opérateur== qui compare un string avec le numéro d'assurance de maladie d'un patient
    // (par exemple, pour patient == "TREMR124520")
    // opérateur== qui compare un string avec le numéro d'assurance de maladie d'un patient
    // (par exemple, pour "TREMR124520" == patient)

    const std::string& getNom() const;
    const std::string& getNumeroAssuranceMaladie() const;
    const std::string& getDateDeNaissance() const;

    void setNom(const std::string& nom);
    void setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie);
    void setDateDeNaissance(const std::string& dateDeNaissance);

private:
    std::string nom_;
    std::string numeroAssuranceMaladie_;
    std::string dateDeNaissance_;
};

#endif // PATIENT_H