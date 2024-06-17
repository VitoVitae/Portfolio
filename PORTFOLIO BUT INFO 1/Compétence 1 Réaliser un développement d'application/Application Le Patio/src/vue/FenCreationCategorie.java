package vue;

import java.io.IOException;

import controleur.CtrlCreationCategorie;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import modele.CategorieSpectateur;

public class FenCreationCategorie extends Stage {
    private CtrlCreationCategorie ctrl;

    public FenCreationCategorie() throws IOException {
        this.setTitle("Créer une catégorie");
        this.setResizable(false);
        Scene scene = new Scene(creerSceneGraph());
        this.setScene(scene);
    }

    public void afficher(CategorieSpectateur categorie) {
        ctrl.afficher(categorie);
    }

    private Pane creerSceneGraph() throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/creationCategorie.fxml"));
        Pane root = loader.load();
        ctrl = loader.getController();
        return root;
    }

    public CtrlCreationCategorie ctrl() {
        return ctrl;
    }
}
