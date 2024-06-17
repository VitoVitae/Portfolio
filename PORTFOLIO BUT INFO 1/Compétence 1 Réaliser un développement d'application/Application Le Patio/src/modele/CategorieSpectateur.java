package modele;

/**
 * Une catégorie de spectateurs.
 */
public class CategorieSpectateur {
    private String nom;
    private String description;
    private Double reduction;
    // Modification par raport à la proposition de correction du diagramme de classe
    // Au lieu d'une hiérarchie de Tarification, on utilise des variables de classes
    // pour représenter les catégories de base

    public CategorieSpectateur(String nom_, String description_, Double reduction_) {
        nom = nom_;
        description = description_;
        reduction = reduction_;
    }

    @Override
    public boolean equals(Object obj) {
        boolean res = false;
        if (obj instanceof CategorieSpectateur) {
            CategorieSpectateur otherObj = (CategorieSpectateur) obj;
            res = this.getNom() == otherObj.getNom();
        }
        return res;
    }

    public String getDescription() {
        return description;
    }

    public String getNom() {
        return nom;
    }

    public Double getReduction() {
        return reduction;
    }

    public void setDescription(String description_) {
        description = description_;
    }

    public void setNom(String nom_) {
        nom = nom_;
    }

    public void setReduction(Double reduction_) {
        reduction = reduction_;
    }

    @Override
    public String toString() {
        return nom + " " + description + " " + reduction;
    }
}
