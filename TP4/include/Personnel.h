#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <memory>
#include <string>
#include "Patient.h"
#include <vector>

class Personnel
{
public:

	Personnel() = default;
	//DONE : Modifier le constructeur pour prendre en considération l'attribut ajouté
	Personnel(const std::string& nom, const std::string& id, const tm& dateAdhesion);

	friend bool operator==(const std::string& id, const Personnel& personnel);
	bool operator==(const std::string& id) const;

	bool operator<(const Personnel& personnel);

	virtual void afficher(std::ostream& stream) const;

	virtual double getSalaireAnnuel() const = 0;

	const std::string& getNom() const;
	const std::string& getId() const;
	bool getEstActif() const;

	void setNom(const std::string& nom);
	void setId(const std::string& id);
	void setEstActif(bool estActif);

protected:

	// Attributs
	std::string nom_;
	std::string id_;
	bool estActif_ = true;
	//DONE : Ajouter l'attribut dateAdhesion_
	tm dateAdhesion_;
};

#endif // PERSONNEL_H