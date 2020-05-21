//! D�finition de la classe Medecin qui repr�sente un m�decin qui travaille � l'h�pital
//! \authors Didier Blach Lafl�che & Maude Tremblay
//! \date 21 Mai 2020

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

    // surcharge interne d'operateurs
    bool operator+= (const Patient& patient);
    bool operator-= (const std::string& numeroAssuranceMaladie);
    bool operator== (const std::string& numeroLicence);
    // surcharge externe d'operateurs
    friend std::ostream& operator<< (std::ostream& stream, const Medecin& medecin);
    friend bool operator==(const std::string& numeroLicence, Medecin medecin);


    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);

    // getters
    const std::string& getNom() const;
    const std::string& getNumeroLicence() const;
    bool getEstActif() const;
    const Specialite getSpecialite() const;
    const size_t getCapacitePatientAssocies() const;
    const size_t getNombrePatientsAssocies() const;
    std::vector<std::shared_ptr<Patient>> getPatientsAssocies();

    //setters
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

    std::vector<std::shared_ptr<Patient>> patientsAssocies_;
  
};

#endif // MEDECIN_H