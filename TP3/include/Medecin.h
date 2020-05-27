#ifndef MEDECIN_H
#define MEDECIN_H

#include <memory>
#include <string>
#include "Patient.h"
#include <vector>

//TODO : Cette classe hérite de la classe Personnel
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

    bool operator+=(Patient* patient);
    bool operator-=(const std::string& numeroAssuranceMaladiePatient);

    //Surchage de la méthode afficher. Elle doit être déclarée virtuelle ici aussi.
    void afficher(std::ostream& stream) const;

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    void incrementNombreConsultations();

    //Surchage de la méthode getSalaireAnnuel. Elle doit être déclarée virtuelle ici aussi.
    double getSalaireAnnuel() const;

    double getPrixConsultation() const;

    //TODO : des getters et des setters peuvent être ajoutés ou enlevés si nécessaire

    const std::string& getNom() const;
    const std::string& getNumeroLicence() const;
    bool getEstActif() const;
    const Specialite getSpecialite() const;
    const size_t getNombrePatientsAssocies() const;

    const std::vector<Patient*>& getPatientsAssocies() const;

    void setNom(const std::string& nom);
    void setNumeroLicence(const std::string& numeroLicence);
    void setEstActif(bool estActif);
    void setSpecialite(Specialite specialite);


    static constexpr size_t SALAIRE_DE_BASE_MEDECIN = 100000;

//TODO : 
//Certains attributs devraient êtres enlevés.
//D'autres attributs doivent être ajoutés. Voir l'énoncé
//Les attributs de cette classe doivent être accessibles aux classes dérivées de cette classe.
//La méthode trouverIndexPatient est une méthode privée
private:
    int trouverIndexPatient(const std::string& numeroAssuranceMaladie);

    // Attributs
    std::string nom_;
    std::string numeroLicence_;
    Specialite specialite_;
    bool estActif_ = true;

    std::vector<Patient*> patientsAssocies_;
};

#endif // MEDECIN_H