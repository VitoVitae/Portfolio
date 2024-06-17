package controleur;

import java.io.IOException;

import javafx.application.Application;
import javafx.stage.Modality;
import javafx.stage.Stage;
import modele.CategorieSpectateur;
import modele.Donnees;
import vue.*;

public final class Main extends Application {
    private static FenCreationCategorie fCreationCategorie;
    private static FenAccueil fAccueil;
    private static FenAPropos fAPropos;

    /**
     * Créer une nouvelle catégorie avec la fenêtre modale de création de catégorie.
     * 
     * @param actuel la catégorie à modifier, ou null pour créer une nouvelle catégorie
     * @return Une nouvelle instance de la classe
     *         {@link modele.CategorieSpectateur}, ou la catégorie actuelle si
     *         l'utilisateur a annulé la création/modifcation.
     */
    public static CategorieSpectateur afficherCreationCategorie(CategorieSpectateur actuel) {
        fCreationCategorie.afficher(actuel);
        fCreationCategorie.showAndWait();
        return fCreationCategorie.ctrl().actuel();
    }

    public static void ajouterCategorie(CategorieSpectateur actuel, boolean modifier) {
        if (modifier) {
            // c'est une modification
            Donnees.modifierCategorie(actuel);
        } else {
            // c'est un ajout
            Donnees.ajouterCategorie(actuel);
        }
    }

    public static void fermerCreationCategorie() {
        fCreationCategorie.close();
    }

    public static void main(String[] args) {
        launch(args);
    }

    public static void quitter() {
        System.exit(0);
    }

    public static void supprimerCategorie(CategorieSpectateur actuel) {
        Donnees.supprimerCategorie(actuel);
    }
    
    public static void afficherAPropos() {
        fAPropos.show();
    }
    
    public static void fermerAPropos() {
        fAPropos.close();
    }

    @Override
    public void start(Stage stage) throws IOException {
        fAccueil = new FenAccueil();

        fCreationCategorie = new FenCreationCategorie();
        fCreationCategorie.initModality(Modality.APPLICATION_MODAL);
        
        fAPropos = new FenAPropos();

        fAccueil.show();

    }
}
