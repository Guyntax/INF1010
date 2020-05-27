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
	Personnel(const std::string& nom, const std::string& id);

	friend bool operator==(const std::string& id, const Personnel& personnel);
	bool operator==(const std::string& id) const;

	// TODO : méthode virtuelle
	void afficher(std::ostream& stream) const;

	//TODO : méthode virtuelle pure à ne pas implémenter dans cette classe
	double getSalaireAnnuel() const;

	const std::string& getNom() const;
	const std::string& getId() const;
	bool getEstActif() const;

	void setNom(const std::string& nom);
	void setId(const std::string& id);
	void setEstActif(bool estActif);

//TODO : Les attributs de cette classe doivent être accessible par les classes des dérivées
private:
	// Attributs
	std::string nom_;
	std::string id_;
	bool estActif_ = true;
};

#endif // PERSONNEL_H