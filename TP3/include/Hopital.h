//! Définition de la classe Hopital qui permet la gestion de l'hôpital.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#ifndef HOPITAL_H
#define HOPITAL_H

#include <string>
#include <vector>

#include "Consultation.h"
#include "GestionnairePersonnels.h"
#include "GestionnairePatients.h"
#include "ConsultationEnligne.h"
#include "ConsultationPhysique.h"

class Hopital
{
public:
    Hopital() = default;
    Hopital(const std::string& nom, const std::string& adresse);

    bool chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients);

    bool operator+=(const Consultation& consultation);
    bool operator+=(const Medecin& medecin);
    bool operator+=(const Patient& patient);

    const std::string& getNom() const;
    const std::string& getAdresse() const;
    GestionnairePersonnels& getGestionnairePersonnels();
    GestionnairePatients& getGestionnairePatients();
    const std::vector<std::shared_ptr<Consultation>>& getConsultations() const;

    void setNom(const std::string& nom);
    void setAdresse(const std::string& adresse);

private:
    std::string nom_;
    std::string adresse_;

    //DONE : À remplacer par gestionnaire personnels
    GestionnairePersonnels gestionnairePersonnels_;
    GestionnairePatients gestionnairePatients_;
    std::vector<std::shared_ptr<Consultation>> consultations_;
};

#endif // HOPITAL_H