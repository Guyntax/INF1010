//! Définition de la classe Hôpital qui permet la gestion de l'hôpital
//! \authors Didier Blach-Lafleche & Maude Tremblay
//! \date 14 juin 2020
#ifndef HOPITAL_H
#define HOPITAL_H

#include <string>
#include <vector>

#include "Consultation.h"
#include "GestionnairePersonnels.h"
#include "GestionnairePatients.h"

class Hopital
{
public:
    enum class TypeConsultation
    {
        first_ = -1,
        ConsultationEnLigne,
        ConsultationPhysique,
        last_
    };

    Hopital() = default;
    Hopital(const std::string& nom, const std::string& adresse);

    bool chargerBaseDeDonnees(const std::string& nomFichierPersonnels, const std::string& nomFichierPatients, const std::string& nomFichierConsultations);
    bool chargerDepuisFichierConsultation(const std::string& nomFichiers);
    double getAncienneteMoyenneDesPersonnels();
    std::vector<std::shared_ptr<Consultation>> getCosultationsEntreDates(tm& date1, tm& date2);

    //! Méthode qui ajoute une consultation à un hopital
    //! \param consultation consultation à ajouter
    //! \return       Un bool qui indique si l'opération a bien fonctionnée
    template <typename consult>
    bool ajouterConsultation(consult& consultation)
    {
        Medecin* medecin = dynamic_cast<Medecin*>(gestionnairePersonnels_.chercherPersonnel(consultation.getMedecin()->getId()));
        if (medecin && medecin->getEstActif())
        {
            Patient* patient = gestionnairePatients_.chercherPatient(consultation.getPatient()->getNumeroAssuranceMaladie());
            if (!patient)
            {
                return false;
            }

            consultations_.push_back(std::make_shared<consult>(consultation));

            Patient* patientDuMedecin = medecin->chercherPatient(patient->getNumeroAssuranceMaladie());
            if (!patientDuMedecin)
            {
                *medecin += patient;
            }
            medecin->incrementNombreConsultations();

            return true;
        }

        return false;
    };

    //! Operateur qui ajoute un personnel à un hopital
    //! \param personnel Personnel à ajouter
    //! \return       Un bool qui indique si l'opération a bien fonctionnée
    template <typename perso>
    bool ajouterPersonnel(perso& personnel)
    {
        return gestionnairePersonnels_.ajouterPersonnel<perso>(personnel);
    }

    //! Operateur qui ajoute un patient à un hopital
    //! \param patient Patient à ajouter
    //! \return       Un bool qui indique si l'opération a bien fonctionnée
    template <typename pat>
    bool ajouterPatient(pat& patient)
    {
        return gestionnairePatients_.ajouterPatient<pat>(patient);
    }

    const std::string& getNom() const;
    const std::string& getAdresse() const;
    GestionnairePersonnels& getGestionnairePersonnels();
    GestionnairePatients& getGestionnairePatients();
    const std::vector<std::shared_ptr<Consultation>>& getConsultations() const;

    void setNom(const std::string& nom);
    void setAdresse(const std::string& adresse);

private:
    bool lireLigneConsultation(const std::string& ligne);

    std::string nom_;
    std::string adresse_;

    GestionnairePersonnels gestionnairePersonnels_;
    GestionnairePatients gestionnairePatients_;
    std::vector<std::shared_ptr<Consultation>> consultations_;
};

#endif // HOPITAL_H