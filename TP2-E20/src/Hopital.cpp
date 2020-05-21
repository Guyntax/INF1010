//! Définition de la classe Hopital qui permet la gestion de l'hôpital
//! \authors Didier Blach Laflèche & Maude Tremblay
//! \date 20 Mai 2020

#include "Hopital.h"

//! Constructeur par paramètre  de la classe Hopital
//! \param nom      Nom de l'hopital
//! \param adresse  Adresse de l'hopital
Hopital::Hopital(const std::string& nom, const std::string& adresse):nom_(nom), adresse_(adresse)
{
}

// TODO : chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients)
// Permet de charger les médecins et les patients depuis les fichiers passés en paramètres.
// Retourne true si les fichiers sont bien chargés , false si non.
bool Hopital::chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients) {
	bool chargeMedecins;
	bool chargePatients;

	chargeMedecins = gestionnaireMedecins_.chargerDepuisFichier(nomFichierMedecins);
	chargePatients = gestionnairePatients_.chargerDepuisFichier(nomFichierPatients);

	if (chargeMedecins && chargePatients) { return true; };
	return false;
}


// TODO : Operateur += qui permet d'ajouter une consultation à la liste consutltations_ 
// Il prend en parametre une reference vers la consultation a ajouter
// Il ajoute la consultation et retourne true si le medecin est actif, existe dans le gestionnaire de medecins 
// et le patient existe dans le gestionnaire de patients.
// Si non il retourne false.

bool Hopital::operator+=(Consultation& consultation){
	if (consultation.getMedecin()->getEstActif() &&
		gestionnaireMedecins_.chercherMedecin((consultation.getMedecin())->getNumeroLicence()) &&
		gestionnairePatients_.chercherPatient((consultation.getPatient())->getNumeroAssuranceMaladie()) ) { 

		consultation_.push_back(consultation);
		return true;
	}
	return false;
};





// TODO : operater += qui ajoute un médecin au gestionnaire de médecins.
// Il prend en parametre une reference vers le medecin a ajouter
// Une seule ligne de code
bool Hopital::operator+=(Medecin& medecin) {
	return gestionnaireMedecins_ += medecin;
};
// TODO : operater += qui ajouté un pateint au gestionnaire de patient.
// Il prend en parametre une reference vers le patient à ajouter
// Une seule ligne de code
bool Hopital::operator+=(Patient& patient) {
	return gestionnairePatients_ += patient;
};


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
GestionnaireMedecins& Hopital::getGesionnaireMedecins()
{
	return gestionnaireMedecins_;
}

//! Méthode qui retourne le gestionnaire des patients
//! \return gestionnaire des patients
GestionnairePatients& Hopital::getGestionnairePatients()
{
	return gestionnairePatients_;
}

// TODO : getConsultations() retourne une reference constante vers le vecteur consultation.
const std::vector<Consultation>& Hopital::getConsultations() {
	return consultation_;
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
