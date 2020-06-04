//! Implémentation de la classe Hopital qui permet la gestion de l'hôpital.
//! \Authors: Didier Blach-Laflèche & Maude Tremblay
//! \date 07 Juin 2020

#include "Hopital.h"


//! Constructeur par paramètre  de la classe Hopital
//! \param nom      Nom de l'hopital
//! \param adresse  Adresse de l'hopital
Hopital::Hopital(const std::string& nom, const std::string& adresse) :nom_(nom), adresse_(adresse)
{
}

//! Methode pour charger la base de donnees de l'hopital
//! \param nomFichierMedecins  le nom du fichier qui contient les informations des medecins
//! \param adresse  nomFichierPatients le nom du fichier qui contient les informations des patients
bool Hopital::chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients)
{
	// Retroune true seulement si les deux opérations fonctionnent
	return gestionnairePersonnels_.chargerDepuisFichier(nomFichierMedecins)
		&& gestionnairePatients_.chargerDepuisFichier(nomFichierPatients);
}

//! Operateur qui ajoute une consultation à un hopital
//! \param consultation à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(const Consultation& consultation)
{	
	
	std::string id = (consultation.Consultation::getMedecin())->Personnel::getId();
	Medecin* medecin = dynamic_cast<Medecin*>(gestionnairePersonnels_.GestionnairePersonnels::chercherPersonnel(id));
	// On vérifie que le medecin existe et est actif
	if (medecin != nullptr && medecin->getEstActif())
	{
		std::string NAS = (consultation.Consultation::getPatient())->Patient::getNumeroAssuranceMaladie();
		Patient* patient = dynamic_cast<Patient*>(gestionnairePatients_.GestionnairePatients::chercherPatient(NAS));
		//On vérifie que le patient existe
		if(patient == nullptr)
		{
			return false;
		}
		else {
			// Vérifier si la consultation est en ligne
			if (dynamic_cast<ConsultationEnligne*>(const_cast<Consultation*>(&consultation))) {

				consultations_.push_back(std::make_shared<ConsultationEnligne>(*dynamic_cast<ConsultationEnligne*>(const_cast<Consultation*>(&consultation))));
			}
			// Vérifier si la consultation est physique
			else if (dynamic_cast<ConsultationPhysique*>(const_cast<Consultation*>(&consultation))) {

				consultations_.push_back(std::make_shared<ConsultationPhysique>(*dynamic_cast<ConsultationPhysique*>(const_cast<Consultation*>(&consultation))));
			}
		
		*medecin += patient; // cherche déjà si le patient est associé au médecin
		medecin->incrementNombreConsultations();
		return true;
		}
	}	
}

//! Operateur qui ajoute un médecin à un hopital
//! \param patient Le patient à ajouter
bool Hopital::operator+=(const Medecin& medecin)
{
	std::shared_ptr<Medecin> med = std::make_shared<Medecin>(medecin);
	//! \return       Un bool qui indique si l'opération a bien fonctionnée
	return gestionnairePersonnels_ += med.get();
}

//! Operateur qui ajoute un patient à un hopital
//! \param patient Le patient à ajouter
bool Hopital::operator+=(const Patient& patient)
{
	std::shared_ptr<Patient> pat = std::make_shared<Patient>(patient);
	//! \return       Un bool qui indique si l'opération a bien fonctionnée
	return gestionnairePatients_ += pat.get();
}

//! Méthode qui retourne le nom de l'hopital
const std::string& Hopital::getNom() const
{
	return nom_; //! \return le nom de l'hopital 
}

//! Méthode qui retourne l'adresse de l'hopital
const std::string& Hopital::getAdresse() const
{
	return adresse_; //! \return l'adresse de l'hopital 
}

//! Méthode qui retourne le gestionnaire des medecins
GestionnairePersonnels& Hopital::getGestionnairePersonnels()
{
	return gestionnairePersonnels_; //! \return gestionnaire des medecins
}

//! Méthode qui retourne le gestionnaire des patients
GestionnairePatients& Hopital::getGestionnairePatients()
{
	return gestionnairePatients_; //! \return gestionnaire des patients
}

//! Méthode qui retourne les consultaions de l'hopital
const std::vector<std::shared_ptr<Consultation>>& Hopital::getConsultations() const
{
	return consultations_; //! \return consultations_
}

//! Méthode qui permet de mettre à jour le nom de l'hopital
//! \Param nom Le nom de l'hopital
void Hopital::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui permet de mettre à jour l'adresse de l'hopital
//! \Param adresse  l'adresse de l'hopital
void Hopital::setAdresse(const std::string& adresse)
{
	adresse_ = adresse;
}

