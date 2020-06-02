//! Implémentation de la classe Hopital qui gère les consultations.
//! \Authurs: Didier Blach-Laflèche & Maude Tremblay
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
	return gestionnairePersonnels_.chargerDepuisFichier(nomFichierMedecins)
		&& gestionnairePatients_.chargerDepuisFichier(nomFichierPatients);
}

//! Operateur qui ajoute une consultation à un hopital
//! \param consultation à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(const Consultation& consultation)
{	
	
	//Hint : conversion dynamique
	//TODO utiliser chercherPersonnel de GestionnairePersonnel pour avoir un pointeur vers le medecin de la consultation.
	std::string id = (consultation.Consultation::getMedecin())->Personnel::getId();
	Medecin* medecin = dynamic_cast<Medecin*>(gestionnairePersonnels_.GestionnairePersonnels::chercherPersonnel(id));
	if (medecin != nullptr && medecin->getEstActif())
	{
		std::string NAS = (consultation.Consultation::getPatient())->Patient::getNumeroAssuranceMaladie();
		Patient* patient = dynamic_cast<Patient*>(gestionnairePatients_.GestionnairePatients::chercherPatient(NAS));
		if(patient == nullptr)
		{
			return false;
		}
		else {


		//consultations_.push_back(std::make_shared<Consultation>(consultation));
		
		medecin->incrementNombreConsultations();
		return true;
		}
	}
		
	//Si le medecin existe et actif, vérifier si le patient n'existe pas dans gestionnaire patient et retourner false.
	// si le patient existe , ajouter la conversation à consultations_ après voir vérifier son type: connsultatioEnligne ou ConsultaitionPhysique
	
	//Chercher si le patient est associé à ce médecin sinon à ajouter le patient au médecin
	//incrementer le nombre de consultation du medecin.

	
}

//! Operateur qui ajoute un médecin à un hopital
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(const Medecin& medecin)
{
	std::shared_ptr<Medecin> med = std::make_shared<Medecin>(medecin);

	return gestionnairePersonnels_ += med.get();
}

//! Operateur qui ajoute un patient à un hopital
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(const Patient& patient)
{
	std::shared_ptr<Patient> pat = std::make_shared<Patient>(patient);
	return gestionnairePatients_ += pat.get();
}

//! Méthode qui retourne le nom de l'hopital
//! \return le nom de l'hopital 
const std::string& Hopital::getNom() const
{
	return nom_;
}

//! Méthode qui retourne l'adresse de l'hopital
//! \return l'adresse de l'hopital 
const std::string& Hopital::getAdresse() const
{
	return adresse_;
}

//! Méthode qui retourne le gestionnaire des medecins
//! \return gestionnaire des medecins
GestionnairePersonnels& Hopital::getGestionnairePersonnels()
{
	return gestionnairePersonnels_;
}

//! Méthode qui retourne le gestionnaire des patients
//! \return gestionnaire des patients
GestionnairePatients& Hopital::getGestionnairePatients()
{
	return gestionnairePatients_;
}

//! Méthode qui retourne les consultaions de l'hopital
//! \return consultations_
const std::vector<std::shared_ptr<Consultation>>& Hopital::getConsultations() const
{
	return consultations_;
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

