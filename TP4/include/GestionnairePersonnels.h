//! Définition de la classe GestionnairePersonnels qui permet de gérer le personnel de l'hôpital
//! \authors Didier Blach-Lafleche & Maude Tremblay
//! \date 14 juin 2020
#ifndef GESTIONNAIREPERSONNELS_H
#define GESTIONNAIREPERSONNELS_H

#include <memory>
#include <unordered_map>
#include "Medecin.h"
#include "MedecinResident.h"

class GestionnairePersonnels
{
public:
	enum class TypePersonnel
	{
		first_ = -1,
		Medecin,
		MedecinResident,
		last_
	};

	GestionnairePersonnels() = default;

	Personnel* chercherPersonnel(const std::string& id) const;
	bool chargerDepuisFichier(const std::string& nomFichiers);

	// La méthode prend une référence vers l'objet à ajouter
	// L'implémentation doit être modifié aussi
	// Le nombre des lignes de code maximale est 3 lignes (sans compter la signature, les lignes vides et les lignes avec accolades)
	//! \param objet		Le personnel que l'on veut ajouter
	//! \return             Un bool qui indique si le personnel a ajouté avec succès
	template <typename T>
	bool ajouterPersonnel(const T& objet)
	{
		if (dynamic_cast<Personnel*>(std::make_shared<T>(objet).get()) && !chercherPersonnel(objet.getId())) {
			return personnels_.emplace(objet.getId(), std::make_shared<T>(objet)).second;
		}
		return false;
	};

	// La méthode prend un string qui est l'id de personnel à supprimer
	//! \param id			Le id du personnel à supprimer
	//! \return             Un bool qui indique si le personnel a supprimer avec succès
	template <typename T>
	bool supprimerPesonnel(std::string id) {
		if (chercherPersonnel(id)) {
			return personnels_[id]->setEstActif(false);
		}
	};

	friend std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePesonnel);


	const std::unordered_map<std::string, std::shared_ptr<Personnel>>& getPersonnels() const;


	// Elle retourne unordered_map de string et un pointeur vers le personnel
	// La méthode parcours personnels_ et retourne un unordered_map de type désiré
	//! \return             Une unordered_map de pointeur de personnels dont les clés sont leur id
	template <typename T>
	std::unordered_map<std::string, T*> getPersonnelsAvecType() const {
		std::unordered_map<std::string, T*> map;
		for (auto& element : personnels_) {
			T* casted_element = (dynamic_cast<T*>(element.second.get()));
			if (casted_element) {
				map.emplace(casted_element->getId(), casted_element);
			}
		}
		return map;
	};


	std::vector<std::pair<std::string, std::shared_ptr<Personnel>>> getPersonnelsTriesSuivantSalaireAnnuel() const;


	size_t getNbPersonnels() const;
	size_t getNbMedecins() const;
	size_t getNbMedecinsResidents() const;

private:
	bool lireLignePersonnel(const std::string& ligne);

	std::unordered_map<std::string, std::shared_ptr<Personnel>> personnels_;
};

#endif // GESTIONNAIREPERSONNELS_H