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

    // TODO : Ajouter un paramètre à la méthode. Ce paramètre est le nom du fichier consultation
    bool chargerBaseDeDonnees(const std::string& nomFichierPersonnels, const std::string& nomFichierPatients);

    bool chargerDepuisFichierConsultation(const std::string& nomFichiers);

    // TODO : Ajouter la méthode getAncienneteMoyenneDesPersonnels 
    // Elle retourne la moyenne de l'ancienneté des personnels de type double

    // TODO : Ajouter la méthode getCosultationsEntreDates
    // Deux paramètres : références constantes vers des objets de type tm
    // Elle retourne la moyenne de l'ancienneté des personnels de type double
    // Elle retourne un vecteur de shared_ptr vers Consultation


    // TODO: Remplacer l'opérateur par la méthode générique ajouterConsultation
    // La méthode prend une référence vers l'objet à ajouter
    bool operator+=(Consultation& consultation);
 
    // TODO: Remplacer l'opérateur par la méthode générique ajouterPersonnel
    // La méthode prend une référence vers l'objet à ajouter
    // L'impémentation de cette méthode doit se faire ici.
    // // Le nombre des lignes de code maximale 1 ligne
    bool operator+=(Personnel& personnel);

    // TODO: Remplacer l'opérateur par la méthode générique ajouterPatient
    // La méthode prend une référence vers l'objet à ajouter
    // L'impémentation de cette méthode doit se faire ici.
    // // Le nombre des lignes de code maximale 1 ligne
    bool operator+=(Patient& patient);

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