#ifndef MEDECIN_H
#define MEDECIN_H

#include <memory>
#include <string>
#include <vector>
#include "Patient.h"


class Medecin
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

    //void ajouterPatient(Patient patient);
    //bool supprimerPatient(const std::string& numeroAssuranceMaladie);
    //void afficher(std::ostream& stream) const;

    friend std::ostream& operator<< (std::ostream& stream, const Medecin& medecin);

    bool operator+= (Patient patient);
    bool operator-= (const std::string& numeroAssuranceMaladie);
    bool operator== (const std::string& numeroLicence);

    friend bool operator==(const std::string& numeroLicence, Medecin medecin);

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);

    // TODO : signature des opérateurs à surcharger.
    // opérateur<< qui remplace afficher ok
    // opérateur+= qui remplace ajouterPatient ok
    // opérateur-= qui remplace supprimerPatient ok
    // opérateur== qui compare un string avec le numéro licence du médecin ok
    // (par exemple, pour medecin == "158795")
    // opérateur== qui compare un string avec le numéro licence du médecin
    // (par exemple, pour "158795" == medecin)


    const std::string& getNom() const;
    const std::string& getNumeroLicence() const;
    bool getEstActif() const;
    const Specialite getSpecialite() const;
    const size_t getCapacitePatientAssocies() const;
    const size_t getNombrePatientsAssocies() const;
    std::vector<std::shared_ptr<Patient>> getPatientsAssocies();

    void setNom(const std::string& nom);
    void setNumeroLicence(const std::string& numeroLicence);
    void setEstActif(bool estActif);
    void setSpecialite(Specialite specialite);

private:
    // Attributs
    std::string nom_;
    std::string numeroLicence_;
    Specialite specialite_;
    bool estActif_ = true;

    // TODO: remplacer le tableau par un vecetur de Patient*
    std::vector<std::shared_ptr<Patient>> patientsAssocies_;
    size_t nbPatientsAssocies_;
  
};

#endif // MEDECIN_H