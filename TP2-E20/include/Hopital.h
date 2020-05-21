//! Définition de la classe Hopital qui permet la gestion de l'hôpital
//! \authors Didier Blach Laflèche & Maude Tremblay
//! \date 21 Mai 2020

#ifndef HOPITAL_H
#define HOPITAL_H

#include <string>
#include <vector>

#include "Consultation.h"
#include "GestionnaireMedecins.h"
#include "GestionnairePatients.h"

class Hopital
{
public:
    Hopital() = default;
    Hopital(const std::string& nom, const std::string& adresse);

    bool chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients);
    
    // surcharge interne d'operateurs
    bool operator+=(Consultation& consultation);
    bool operator+=(Medecin& medecin);
    bool operator+=(Patient& patient);

    // getters
    const std::string& getNom() const;
    const std::string& getAdresse() const;
    GestionnaireMedecins& getGesionnaireMedecins();
    GestionnairePatients& getGestionnairePatients();
    const std::vector<Consultation>& getConsultations()const;

    // setters
    void setNom(const std::string& nom);
    void setAdresse(const std::string& adresse);

private:
    // attributs
    std::string nom_;
    std::string adresse_;

    GestionnaireMedecins gestionnaireMedecins_;
    GestionnairePatients gestionnairePatients_;

    std::vector<Consultation> consultation_;
};

#endif // HOPITAL_H